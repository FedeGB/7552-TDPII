#include "CreateUserEvent.h"

CreateUserEvent::CreateUserEvent() {
}

CreateUserEvent::CreateUserEvent(struct mg_connection* nco, struct http_message* hme) {
	this->nc = nco;
	this->hm = hme;
	this->methodType = "POST";

}

CreateUserEvent::~CreateUserEvent() {

}

bool CreateUserEvent::validateInput() {
	bool parentValidation = EventHandler::validateInput();
	if(!parentValidation) return parentValidation;
	// TODO: Validate content type header is application/json

	Json::Reader r = Json::Reader();
	Json::Value val = Json::Value();
	r.parse(hm->body.p,val);
	//std::cout << val.get("password", "").asString() << std::endl;
	if(val.get("username", "").asString().compare("") == 0) {
		this->response(2, "Missing parameters", (Json::Value)0);
		return false;
	}
	if(val.get("name", "").asString().compare("") == 0) {
		this->response(2, "Missing parameters", (Json::Value)0);
		return false;
	}
	if(val.get("password", "").asString().compare("") == 0) {
		this->response(2, "Missing parameters", (Json::Value)0);
		return false;
	}

	return true;
}

void CreateUserEvent::handle(Manager* manager, SharedManager* sManager) {
	bool validation = this->validateInput();
	if(validation) {
		bool userWasCreated = manager->createUser(hm->body.p);
		if(userWasCreated) {
			Json::Reader r = Json::Reader();
			Json::Value val = Json::Value();
			r.parse(hm->body.p, val);
			User* user = manager->getUser(val.get("username", "").asString());
			Json::Value userJson = user->getJson(false);
			userJson["sex"] = val.get("sex", "").asString();
			long id = sManager->postUser(userJson);
			if(id) {
				user->setId((int)id);
				manager->updateUser(user);
				this->response(0, "Registered", (Json::Value)0);
			} else {
				manager->deleteUser(val.get("username", "").asString());
				this->response(1, "Already Registered", (Json::Value)0);	
			}
			delete user;
		} else {
			this->response(1, "Already Registered", (Json::Value)0);
		}
	}
}