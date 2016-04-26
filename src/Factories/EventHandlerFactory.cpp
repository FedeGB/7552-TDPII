#include "EventHandlerFactory.h"


EventHandlerFactory::EventHandlerFactory() {

}

EventHandlerFactory::~EventHandlerFactory() {

}

EventHandler* EventHandlerFactory::getEventHandler(struct mg_connection* nc, struct http_message* hm) {
	EventHandler* handler = NULL;
	if (mg_vcmp(&hm->uri, "/users/create") == 0) {
		handler = new CreateUserEvent(nc, hm);
	} else if(mg_vcmp(&hm->uri, "/users/login") == 0) {
		handler = new LoginUserEvent(nc, hm);
	} else if(mg_vcmp(&hm->uri, "/users/get") == 0) {
		handler = new GetUserDataEvent(nc, hm);
	} else if(mg_vcmp(&hm->uri, "/users/like") == 0) {
		handler = new SaveUserLike(nc, hm);
	} else if(mg_vcmp(&hm->uri, "/conversations/get") == 0) {
		handler = new GetConversationEvent(nc, hm);
	} else if(mg_vcmp(&hm->uri, "/message/save") == 0) {
		handler = new SaveMessageEvent(nc, hm);
	} else {
		handler = new NotAllowedEvent(nc, hm);
	}
	return handler;
}
