#ifndef CREATEUSEREVENT_H_
#define CREATEUSEREVENT_H_

#include "EventHandler.h"
#include "../Manager.h"

class CreateUserEvent: public EventHandler {

public:
	CreateUserEvent(struct mg_connection*, struct http_message*);
	virtual ~CreateUserEvent();

	bool validateInput();
	void handle();

};

#endif /* CREATEUSEREVENT_H_ */