#ifndef EVENTHANDLERFACTORY_H_
#define EVENTHANDLERFACTORY_H_

#include "Factory.h"
#include "../HttpEvents/CreateUserEvent.h"
#include "../HttpEvents/NotAllowedEvent.h"
#include "../HttpEvents/LoginUserEvent.h"
#include "../HttpEvents/GetUserDataEvent.h"
#include "../HttpEvents/GetConversationEvent.h"

class EventHandlerFactory: public Factory {

public:
	EventHandlerFactory();
	virtual ~EventHandlerFactory();
	EventHandler* getEventHandler(struct mg_connection*, struct http_message*);
};

#endif /* EVENTHANDLERFACTORY_H_*/