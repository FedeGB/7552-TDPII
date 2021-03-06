#ifndef GETUSERDATAEVENT_H_
#define GETUSERDATAEVENT_H_

#include "EventHandler.h"

class GetUserDataEvent: public EventHandler {
public:
	GetUserDataEvent();
	GetUserDataEvent(struct mg_connection*, struct http_message*, string parameter);
	~GetUserDataEvent();
	void handle(Manager*, SharedManager*);

protected:
	bool validateInput();
	string parameter;

};

#endif /* GETUSERDATAEVENT_H_ */