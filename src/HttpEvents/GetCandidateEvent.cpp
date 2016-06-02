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
			this->response(1, "There was an error with the Server", (Json::Value)0);
			return;
		}
		Json::Value myShareUser = sManager->getUser(std::to_string(myAppUser->getId()));
		while(it != sharedUsers.end() && act < max) {
		    const Json::Value& user = *it;
		    User* otherUser = manager->getUser(user.get("email", "").asString());
			std::cout << user.get("email", "").asString() << std::endl;
		    if(!otherUser) { // Usuario de shared no esta en este server
		    	it++;
		    	continue;
		    }
		    if(otherUser->getUsername().compare(myAppUser->getUsername()) == 0) {
		    	it++;
		    	continue;	
		    }
		    Like* wasSeen = manager->getLike(myAppUser->getUsername() + otherUser->getUsername());
		    if(wasSeen != NULL) { // Si ya le di like/dislike no lo paso
		    	delete wasSeen;
		    	it++;
		    	continue;
		    }
		    // TODO: Location comparison
		    Json::Value myInterests = myShareUser.get("interests", Json::Value(Json::arrayValue));
		    Json::ValueConstIterator myInterestsIt = myInterests.begin();
		    while(myInterestsIt != myInterests.end()) {

		    	myInterestsIt++;
		    }
		    returnCandidates["candidates"].append(user);
			it++;
			act++;
			delete otherUser;
		}
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