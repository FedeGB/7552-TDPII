#include "LoginUserEvent.h"

#include "time.h"
#include <sstream>

string getTokenFromURL(string url){
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
	// Read header
	char base[100];
	struct mg_str *cl_header = mg_get_http_header(hm, "Authorization");
	mg_get_http_var(cl_header, "Basic", base, sizeof(base));
	string output = getTokenFromURL(cl_header->p);
	string decoded = base64_decode(output);
	int separator = decoded.find(":");
	string user = decoded.substr(0, separator);
	string passStr = decoded.substr(separator+1, decoded.length());
	User* userFound = manager->getUser(user);
	Json::Value jsonValue = Json::Value();
	string token = "";

	char *hashedPass = new char[passStr.length() + 1];
	strcpy(hashedPass, passStr.c_str());
	string hashedPassResult = SHA256(hashedPass);
	delete [] hashedPass;

	if(userFound && !userFound->getUsername().empty()) {
		if (userFound->getPassword().compare(hashedPassResult) == 0) {
			userFound->loginNow();
			std::cout << "LOGIN: " << userFound->getUsername() << std::endl;
			token = userFound->getUsername();
			token.append(":");
			token.append(userFound->getPassword());
			time_t time = std::time(0);
			std::stringstream ss;
			ss << time;
			string ts = ss.str();
			token.append(ts);

			const unsigned char *t = reinterpret_cast<const unsigned char *>( token.c_str());
			//User *userFound = manager->getUser(user);
			token = base64_encode(t, token.length());
			userFound->setToken(token);
			manager->updateUser(userFound);
			jsonValue["result"] = "OK";
		} else {
			jsonValue["result"] = "Invalid password";
		}
	}
	jsonValue["token"] = token;
	if(!token.empty()) {
		this->response(0, "Success", jsonValue);
	} else {
		this->response(1, "Invalid User or Password", jsonValue);
	}
}


bool LoginUserEvent::validateInput() {
	bool parentValidation = EventHandler::validateInput();
	if(!parentValidation) return parentValidation;
	return true;
}