#ifndef NOTALLOWEDEVENT_H_
#define NOTALLOWEDEVENT_H_

#include "EventHandler.h"

class NotAllowedEvent: public EventHandler {
	
public:
	NotAllowedEvent();
	virtual ~NotAllowedEvent();
	virtual void handle(Manager*);

};

#endif /* NOTALLOWEDEVENT_H_ */