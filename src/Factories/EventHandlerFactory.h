#ifndef EVENTHANDLERFACTORY_H_
#define EVENTHANDLERFACTORY_H_

#include "Factory.h"
#include "../HttpEvents/CreateUserEvent.h"
#include "../HttpEvents/NotAllowedEvent.h"

class EventHandlerFactory: public Factory {

public:
	EventHandlerFactory();
	virtual ~EventHandlerFactory();
	EventHandler* getEventHandler(struct mg_connection*, struct http_message*);
};

#endif /* EVENTHANDLERFACTORY_H_*/