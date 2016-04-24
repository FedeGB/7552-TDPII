#ifndef EVENTHANDLERFACTORY_H_
#define EVENTHANDLERFACTORY_H_

#include <string>
#include "../HttpEvents/CreateUserEvent.h"

class EventHandlerFactory {

public:
	EventHandlerFactory();
	virtual ~EventHandlerFactory();
	EventHandler* getEventHandler(struct mg_connection*, struct http_message*);
};

#endif /*EVENTHANDLERFACTORY_H_*/