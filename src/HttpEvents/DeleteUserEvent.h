//
// Created by Juan Manuel Hidalgo on 27/4/16.
//

#ifndef TINDER_DELETEUSEREVENT_H
#define TINDER_DELETEUSEREVENT_H

#include "EventHandler.h"

class DeleteUserEvent : public EventHandler{

public:
	DeleteUserEvent();
	DeleteUserEvent(struct mg_connection*, struct http_message*);
	virtual ~DeleteUserEvent();
	void handle(Manager*);

protected:
	bool validateInput();

};


#endif //TINDER_DELETEUSEREVENT_H
