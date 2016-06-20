#ifndef GETCONVERSATIONEVENT_H_
#define GETCONVERSATIONEVENT_H_

#include "EventHandler.h"


class GetConversationEvent: public EventHandler {
public:
	GetConversationEvent();
	GetConversationEvent(struct mg_connection*, struct http_message*);
	~GetConversationEvent();
	void handle(Manager*, SharedManager*);

protected:
	bool validateInput();
};

#endif /* GETCONVERSATIONEVENT_H_ */