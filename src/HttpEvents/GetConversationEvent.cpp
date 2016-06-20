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
	// Validar header y token para ver si es correcto el acceso!!!
	char user1[100], user2[100];
    mg_get_http_var(&hm->query_string, "user1", user1, sizeof(user1));
    mg_get_http_var(&hm->query_string, "user2", user2, sizeof(user2));
    std::string user1Str(user1);
    std::string user2Str(user2);
    if(user1Str.empty() || user2Str.empty()) {
    	this->response(2, "Missing parameters", Json::Value());
    	return false;
    }
	return true;
}

void GetConversationEvent::handle(Manager* manager, SharedManager* sManager) {
	if(this->validateInput()) {
	    char user1[100], user2[100];
	    mg_get_http_var(&hm->query_string, "user1", user1, sizeof(user1));
	    mg_get_http_var(&hm->query_string, "user2", user2, sizeof(user2));
	    std::string user1Str(user1);
	    std::string user2Str(user2);
	    Conversation* conver = manager->getConversation(user1Str, user2Str);
		vector<Message*> messages = manager->getMessages(user1Str, user2Str);
		Json::Value event;
		Json::Value vec(Json::arrayValue);
		for (int i = 0 ; i < messages.size() ; i++){
			vec.append(messages.at(i)->getJson());
		}
		//vec.append(Json::Value(2));
		//vec.append(Json::Value(3));

		event["messages"] = vec;
		std::cout << event << std::endl;

	    this->response(0, "", event);
	}
}