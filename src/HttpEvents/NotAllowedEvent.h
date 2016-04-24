#ifndef NOTALLOWEDEVENT_H_
#define NOTALLOWEDEVENT_H_

#include "EventHandler.h"

class NotAllowedEvent: public EventHandler {
	
public:
	NotAllowedEvent();
	virtual void ~NotAllowedEvent();
	virtual void handle();

};

#endif /* NOTALLOWEDEVENT_H_ */