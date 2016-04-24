#ifndef GETUSERDATAEVENT_H_
#define GETUSERDATAEVENT_H_

#include "EventHandler.h"

class GetUserDataEvent: public EventHandler {
public:
	GetUserDataEvent();
	GetUserDataEvent(struct mg_connection*, struct http_message*);
	~GetUserDataEvent();
	void handle(Manager*);

protected:
	bool validateInput();

};

#endif /* GETUSERDATAEVENT_H_ */