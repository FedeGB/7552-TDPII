#include "GetConversationEvent.h"

GetConversationEvent::GetConversationEvent() {

}

GetConversationEvent::GetConversationEvent(struct mg_connection* nco, struct http_message* hme) {
	this->nc = nco;
	this->hm = hme;
	this->methodType = "GET";
}

GetConversationEvent::~GetConversationEvent() {

}

bool GetConversationEvent::validateInput() {
	bool parentValidation = EventHandler::validateInput();
	if(!parentValidation) return parentValidation;
	struct mg_str *cl_header = mg_get_http_header(hm, "Token");
	if(!cl_header) {
		this->response(2, "Invalid Token", returnEmptyJsonObject());
    	return false;
	}
    struct mg_str *u1_header = mg_get_http_header(hm, "user1");
    struct mg_str *u2_header = mg_get_http_header(hm, "user2");
    if(!u1_header || !u2_header) {
    	this->response(2, "Missing parameters", returnEmptyJsonObject());
    	return false;
    }
    std::string user1Str = getHeaderParam(u1_header->p);
    std::string user2Str = getHeaderParam(u2_header->p);
    if(user1Str.empty() || user2Str.empty()) {
    	this->response(2, "Missing parameters", returnEmptyJsonObject());
    	return false;
    }
	return true;
}

void GetConversationEvent::handle(Manager* manager, SharedManager* sManager) {
	if(this->validateInput()) {
		struct mg_str *cl_header = mg_get_http_header(hm, "Token");
	    struct mg_str *u1_header = mg_get_http_header(hm, "user1");
	    struct mg_str *u2_header = mg_get_http_header(hm, "user2");
	    if(!u1_header || !u2_header) {
	    	this->response(2, "Missing parameters", returnEmptyJsonObject());
	    	return;
	    }
	    std::string user1Str = getHeaderParam(u1_header->p);
	    std::string user2Str = getHeaderParam(u2_header->p);
	    std::string token(getHeaderParam(cl_header->p));
	    User* user1 = manager->getUser(user1Str);

		User* userFound = manager->getUser(user1Str);
		if(!cl_header) {
			this->response(1, "Token missing", returnEmptyJsonObject());
			return;
		}

		if(token.compare(userFound->getToken()) != 0){
			this->response(1, "Invalid Token", returnEmptyJsonObject());
			return;
		}

		Conversation* conver = manager->getConversation(user1Str, user2Str);
		vector<Message*> messages = manager->getMessages(user1Str, user2Str);
		Json::Value event;
		Json::Value vec(Json::arrayValue);
		for (int i = 0 ; i < messages.size() ; i++){
			vec.append(messages.at(i)->getJson());
			delete messages.at(i);
		}
		delete conver;
		event["messages"] = vec;
		// std::cout << event << std::endl;
		this->response(0, "", event);

	}
}