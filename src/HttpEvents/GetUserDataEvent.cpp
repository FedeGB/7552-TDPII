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
	    //char username[100];
	    //mg_get_http_var(&hm->query_string, "username", username, sizeof(username));
	    User* user = manager->getUser(this->parameter);
	    this->response(0, "", user->getJson()); 
	    // Si es el API call que se usa para obtener toda la info del usuario,
		// quedaria agergarle la info que se traiga del shared server en el get json o
		// hacer otro getJson con toda la data en si y no solo la del app server
	//}
}