#include "EventHandlerFactory.h"


EventHandlerFactory::EventHandlerFactory() {

}

EventHandlerFactory::~EventHandlerFactory() {

}

EventHandler* EventHandlerFactory::getEventHandler(struct mg_connection* nc, struct http_message* hm) {
	EventHandler* handler = NULL;
	if (mg_vcmp(&hm->uri, "/users/create") == 0) {
		handler = new CreateUserEvent(nc, hm);
	} else {
		handler = new NotAllowedEvent();
	}
	return handler;
}
