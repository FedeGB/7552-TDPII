#ifndef CREATEUSEREVENT_H_
#define CREATEUSEREVENT_H_

#include "EventHandler.h"

class CreateUserEvent: public EventHandler {

public:
	CreateUserEvent();
	CreateUserEvent(struct mg_connection*, struct http_message*);
	virtual ~CreateUserEvent();
	void handle(Manager*, SharedManager*);

protected:
	bool validateInput();

};

#endif /* CREATEUSEREVENT_H_ */