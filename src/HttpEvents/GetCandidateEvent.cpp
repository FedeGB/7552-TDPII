#include "GetCandidateEvent.h"


GetCandidateEvent::GetCandidateEvent() {
}

GetCandidateEvent::GetCandidateEvent(struct mg_connection* nco, struct http_message* hme, std::string parameter) {
	this->nc = nco;
	this->hm = hme;
	this->methodType = "GET";
	this->parameter = parameter;
}

GetCandidateEvent::~GetCandidateEvent() {
}

void GetCandidateEvent::handle(Manager* manager, SharedManager* sManager) {
	bool validation = this->validateInput();
	if(validation) {
		Json::Value sharedUsers = sManager->getUsers();
		Json::ValueConstIterator it = sharedUsers.begin();
		int max = 10;
		int act = 0;
		Json::Value returnCandidates = Json::Value();
		Json::Value candidates = Json::Value(Json::arrayValue);
		returnCandidates["candidates"] = candidates;
		User* myAppUser = manager->getUser(this->parameter);
		if(!myAppUser) {
			this->response(1, "There was an error with the Server", Json::Value());
			return;
		}

		struct mg_str *cl_header = mg_get_http_header(hm, "Token");
		if(!cl_header) {
			this->response(1, "Token missing", Json::Value());
			return;
		}
		std::string token(getHeaderParam(cl_header->p));
		if(token.compare(myAppUser->getToken()) != 0) {
			this->response(1, "Invalid Token", Json::Value());
			return;
		}

		if(this->checkDailyLimit(myAppUser)) {
			myAppUser->updateLastRequest();
			manager->updateUser(myAppUser);
			this->response(2, "Maximum candidates per day reached", Json::Value());
			return;
		}
		if(myAppUser->hasReachedMaxCandidatesSend()) {
			myAppUser->resetCandidatesSend();
			manager->updateUser(myAppUser);
		}
		Json::Value myShareUser = sManager->getUser(std::to_string(myAppUser->getId()));
		std::map<std::string,bool> interestMap;
		while(it != sharedUsers.end() && act < max) {
		    const Json::Value& user = *it;
		    Json::Value modifiUser = user;
		    User* otherUser = manager->getUser(user.get("email", "").asString());
		    if(!otherUser) { // Usuario de shared no esta en este server
		    	delete otherUser;
		    	it++;
		    	continue;
		    }
		    if(otherUser->getUsername().compare(myAppUser->getUsername()) == 0) { // Si soy yo
		    	delete otherUser;
		    	it++;
		    	continue;	
		    }
		    Like* wasSeen = manager->getLike(myAppUser->getUsername() + otherUser->getUsername());
		    if(wasSeen != NULL) { // Si ya le di like/dislike no lo paso
		    	delete wasSeen;
		    	delete otherUser;
		    	it++;
		    	continue;
		    }
		    if(!otherUser->returnAsCandidate()) { // Si es popular (1%) y salio sorteado (?) no se pasa como candidato
		    	delete otherUser;
		    	it++;
		    	continue;
		    }
		    // Si no esta dentro de mi rango de edades definidas
		    if(user.get("age", 18).asInt() < myAppUser->getMinAge() || user.get("age", 18).asInt() > myAppUser->getMaxAge()) {
		    	it++;
		    	continue;
		    }
		    double myLon = myShareUser.get("location", Json::Value()).get("longitude", 0).asDouble();
		    double myLat = myShareUser.get("location", Json::Value()).get("latitude", 0).asDouble();
		    double otherLon = user.get("location", Json::Value()).get("longitude", 0).asDouble();
		    double otherLat = user.get("location", Json::Value()).get("latitude", 0).asDouble();
		    float distance = harvestineDistance(myLat, myLon, otherLat, otherLon);
		    if(distance > myAppUser->getDistance()) { // Si el candidato esta lejos (para mi valor)
		    	it++;
		    	continue;
		    }
		    Json::Value myInterests = myShareUser.get("interests", Json::Value(Json::arrayValue));
		    Json::ValueConstIterator myInterestsIt = myInterests.begin();
		    bool isCandidate = true;
		    std::string mapKey;
		    while(myInterestsIt != myInterests.end() && isCandidate) {
		    	if((*myInterestsIt).get("category", "").asString().compare("sex") == 0) {
		    		std::string interestedIn = (*myInterestsIt).get("value", "").asString();
		    		if(interestedIn.substr(0, 1).compare(user.get("sex", "").asString()) != 0) {
		    			isCandidate = false;
		    			break;
		    		}
		    	}
		    	mapKey = (*myInterestsIt).get("category", "").asString() + (*myInterestsIt).get("value", "").asString();
		    	std::transform(mapKey.begin(), mapKey.end(), mapKey.begin(), ::tolower);
		    	mapKey.erase(std::remove_if(mapKey.begin(), mapKey.end(), ::isspace), mapKey.end());
		    	interestMap[mapKey] = true;
		    	myInterestsIt++;
		    }
		    Json::Value otherInterests = user.get("interests", Json::Value(Json::arrayValue));
		    Json::ValueConstIterator otherInterestsIt = otherInterests.begin();
		    Json::Value commonInterests = Json::Value(Json::arrayValue);
		    while(otherInterestsIt != otherInterests.end() && isCandidate) {
		    	if((*otherInterestsIt).get("category", "").asString().compare("sex") == 0) {
		    		std::string interestedIn = (*otherInterestsIt).get("value", "").asString();
		    		if(interestedIn.substr(0, 1).compare(myShareUser.get("sex", "").asString()) != 0) {
		    			isCandidate = false;
		    			break;
		    		}
		    	}
		    	mapKey = (*otherInterestsIt).get("category", "").asString() + (*otherInterestsIt).get("value", "").asString();
		    	std::transform(mapKey.begin(), mapKey.end(), mapKey.begin(), ::tolower);
		    	mapKey.erase(std::remove_if(mapKey.begin(), mapKey.end(), ::isspace), mapKey.end());
		    	std::map<std::string,bool>::iterator it;
		    	it = interestMap.find(mapKey);
		    	if(it !=interestMap.end()) {
		    		commonInterests.append((*otherInterestsIt));
		    	}
		    	otherInterestsIt++;
		    }
		    if(commonInterests.size() < 1) {
		    	isCandidate = false;
		    }
		    // TODO: Tomar en cuenta rango de edad del otro usuario (ya que si yo no caigo en el rango de el otro
		    // nunca se va a dar un match, a menos que el otro cambie el rango, que puede pasar o no)
		    if(isCandidate) {
		    	modifiUser.removeMember("location");
		    	modifiUser["distance"] = (double)distance;
		    	modifiUser.removeMember("interests");
		    	modifiUser["interests"] = commonInterests;
		    	returnCandidates["candidates"].append(modifiUser);
				act++;
		    }
			it++;
			interestMap.clear();
			delete otherUser;
		}
		myAppUser->updateLastRequest();
		myAppUser->updateCandidatesSend((int)returnCandidates["candidates"].size());
		manager->updateUser(myAppUser);
		delete myAppUser;
		this->response(0, "", returnCandidates);
	}
}

bool GetCandidateEvent::validateInput() {
    bool parentValidation = EventHandler::validateInput();
    if(!parentValidation) return parentValidation;

    // Validar header y token para ver si es correcto el acceso!!!
    return true;
}


bool GetCandidateEvent::checkDailyLimit(User* user) {
	if(user->requestWasToday() && user->hasReachedMaxCandidatesSend()) {
		return true;
	}
	return false;
}