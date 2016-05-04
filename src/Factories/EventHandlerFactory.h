#ifndef EVENTHANDLERFACTORY_H_
#define EVENTHANDLERFACTORY_H_

#include "Factory.h"
#include "../HttpEvents/CreateUserEvent.h"
#include "../HttpEvents/NotAllowedEvent.h"
#include "../HttpEvents/LoginUserEvent.h"
#include "../HttpEvents/GetUserDataEvent.h"
#include "../HttpEvents/GetConversationEvent.h"
#include "../HttpEvents/SaveMessageEvent.h"
#include "../HttpEvents/SaveUserLike.h"
#include "../HttpEvents/GetUserMatches.h"
#include "../HttpEvents/DeleteUserEvent.h"
#include "../HttpEvents/GetUsers.h"
#include "../HttpEvents/UpdateUserData.h"


class EventHandlerFactory: public Factory {

public:
	EventHandlerFactory();
	virtual ~EventHandlerFactory();
	EventHandler* getEventHandler(struct mg_connection*, struct http_message*);
};

#endif /* EVENTHANDLERFACTORY_H_*/