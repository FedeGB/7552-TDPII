#include "CreateUserEvent.h"

CreateUserEvent::CreateUserEvent(struct mg_connection* nco, struct http_message* hme) {
	this->nc = nco;	
	this->hm = hme;
	this->methodType = "POST";
}

bool CreateUserEvent::validateInput() {
	if(mg_vcmp(&hm->method, this->methodType) != 0) {
		this->respondNotAllowedMethod();
		return false;
	}
	// TODO: Validate content type header is application/json

	Json::Reader r = Json::Reader();
	Json::Value val = Json::Value();
	r.parse(this->hm->body.p.c_str(),val);
	if(val.get("username", "").asString().compare("")) {
		this->response(nc, 2, "Missing parameters", 0);
		return false;
	}
	if(val.get("name", "").asString().compare("")) {
		this->response(nc, 2, "Missing parameters", 0);
		return false;
	}
	if(val.get("password", "").asString().compare("")) {
		this->response(nc, 2, "Missing parameters", 0);
		return false;
	}

	return true;
}

void CreateUserEvent::handle() {
	bool validation = this->validateInput();
	if(validation) {
		Manager* manager = new Manager();
		bool userWasCreated = manager->createUser(hm->body.p);
		delete manager;
		if(userWasCreated) {
			this->response(nc, 0, "Registered", 0);
		} else {
			this->response(nc, 1, "Already Registered", 0);
		}
	}
}