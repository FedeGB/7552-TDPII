#include "LoginUserEvent.h"
#include "../Utils.h"



string getParameter2(string url){
	url = url.substr(1, url.length());
	int positionSpace = url.find(" ");
	string substring = url.substr(positionSpace+1, url.length());
	int positionEnter = substring.find("\r");
	string token = substring.substr(0, positionEnter);
	return token;
}

LoginUserEvent::LoginUserEvent() {

}

LoginUserEvent::LoginUserEvent(struct mg_connection* nco, struct http_message* hme) {
	this->nc = nco;	
	this->hm = hme;
	this->methodType = "GET";

}

LoginUserEvent::~LoginUserEvent() {

}



void LoginUserEvent::handle(Manager* manager, SharedManager* sManager) {
	bool validation = this->validateInput();
	//if(validation) {
		/* Get form variables */
		char ssid[100];

		char base[100];
		mg_http_parse_header(
			mg_get_http_header(hm, "Authorization"), "ssid", ssid, sizeof(ssid));
		struct mg_str *cl_header = mg_get_http_header(hm, "Authorization");
		mg_get_http_var(cl_header, "Basic", base, sizeof(base));


		string output = getParameter2(cl_header->p);
		string decoded = base64_decode(output);
	    int separator = decoded.find(":");
	    string user = decoded.substr(0, separator);
		string passStr = decoded.substr(separator+1, decoded.length());

		User* userFound = manager->getUser(user);
		std::cout << "LOGIN: " << userFound->getUsername() << std::endl;
		Json::Value jsonValue = Json::Value();
		std::string token = userFound->getUsername();
		if(userFound && !userFound->getUsername().empty()) {
			if (passStr.compare(userFound->getPassword()) == 0){
				userFound->loginNow();
				jsonValue["result"] = "OK";
				// jsonValue["data"] = userFound->getJson(); Quizas pasarle mas data
				token = "hola";  // TODO fixear esto
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
	//}
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