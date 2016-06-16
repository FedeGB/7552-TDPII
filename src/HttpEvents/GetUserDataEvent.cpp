#include "GetUserDataEvent.h"

GetUserDataEvent::GetUserDataEvent() {

}

GetUserDataEvent::GetUserDataEvent(struct mg_connection* nco, struct http_message* hme, string parameter) {
	this->nc = nco;
	this->hm = hme;
	this->methodType = "GET";
	this->parameter = parameter;
}

GetUserDataEvent::~GetUserDataEvent() {

}


bool GetUserDataEvent::validateInput() {
	bool parentValidation = EventHandler::validateInput();
	if(!parentValidation) return parentValidation;
	// TODO VALIDATE HEADER Y TOKEN
	char username[100];
    mg_get_http_var(&hm->query_string, "username", username, sizeof(username));
    std::string userStr(username);
    if(userStr.empty()) {
    	this->response(2, "Missing parameters", (Json::Value)0);
    	return false;
    }
	return true;
}

void GetUserDataEvent::handle(Manager* manager, SharedManager* sManager) {
	//bool validation = this->validateInput();
	//if(validation) {
	    User* user = manager->getUser(this->parameter);
	    Json::Value sharedUserData = sManager->getUser(std::to_string(user->getId()));
	    sharedUserData["username"] = user->getJson().get("username", "").asString();
	    user->updateWithJson(sharedUserData); // Update de lo que viene de Shared
	    manager->updateUser(user);
	    sharedUserData["distance"] = user->getDistance();
	    sharedUserData["ageRange"] = user->getJson().get("ageRange", Json::Value());
	    this->response(0, "", sharedUserData); 
	    delete user;
	//}
}