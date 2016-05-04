#include "LoginUserEvent.h"

LoginUserEvent::LoginUserEvent() {

}

LoginUserEvent::LoginUserEvent(struct mg_connection* nco, struct http_message* hme) {
	this->nc = nco;	
	this->hm = hme;
	this->methodType = "GET";

}

LoginUserEvent::~LoginUserEvent() {

}



void LoginUserEvent::handle(Manager* manager) {
	bool validation = this->validateInput();
	if(validation) {
		char user[100], password[100];
		/* Get form variables */
		mg_get_http_var(&hm->query_string, "user", user, sizeof(user));
		mg_get_http_var(&hm->query_string, "password", password, sizeof(password));
		std::string passStr(password);
		User* userFound = manager->getUser(user);
		std::cout << "LOGIN: " << userFound->getUsername() << std::endl;
		Json::Value jsonValue = Json::Value();
		std::string token = "";
		if(userFound && !userFound->getUsername().empty()) {
			if (passStr.compare(userFound->getPassword()) == 0){
				userFound->loginNow();
				jsonValue["result"] = "OK";
				// jsonValue["data"] = userFound->getJson(); Quizas pasarle mas data
				token = userFound->getToken();  // TODO fixear esto
			} else {
				jsonValue["result"] = "FAIL";
			}
		} else {
			jsonValue["result"] = "FAIL";
		}
		Json::Value param = Json::Value();
		jsonValue["token"] = token;
		if(!token.empty()) {
			this->response(0, "Success", jsonValue);
		} else {
			this->response(1, "Invalid User or Password", jsonValue);
		}
	}
}


bool LoginUserEvent::validateInput() {
	bool parentValidation = EventHandler::validateInput();
	if(!parentValidation) return parentValidation;
	// TODO VALIDATE HEADER
	char user[100], password[100];
	mg_get_http_var(&hm->query_string, "user", user, sizeof(user));
	mg_get_http_var(&hm->query_string, "password", password, sizeof(password));
	std::string userStr(user);
	std::string passStr(password);
	if(userStr.empty() || passStr.empty()) {
		this->response(2, "Missing parameters", (Json::Value)0);
		return false;
	}
	return true;
}