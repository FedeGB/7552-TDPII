#ifndef NOTALLOWEDEVENT_H_
#define NOTALLOWEDEVENT_H_

#include "EventHandler.h"

class NotAllowedEvent: public EventHandler {
	
public:
	NotAllowedEvent();
	NotAllowedEvent(struct mg_connection*, struct http_message*);
	virtual ~NotAllowedEvent();
	void handle(Manager*, SharedManager*);

};

#endif /* NOTALLOWEDEVENT_H_ */