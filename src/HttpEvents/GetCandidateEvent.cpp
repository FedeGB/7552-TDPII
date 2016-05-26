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
		while(it != sharedUsers.end() && act < max) {
		    const Json::Value& user = *it;
		    returnCandidates["candidates"].append(user);
			it++;
			act++;
		}
		this->response(0, "", returnCandidates);
	}
}

bool GetCandidateEvent::validateInput() {
    bool parentValidation = EventHandler::validateInput();
    if(!parentValidation) return parentValidation;
    // Validar header y token para ver si es correcto el acceso!!!
    return true;
}