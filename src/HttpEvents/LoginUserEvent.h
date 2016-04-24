#ifndef LOGINUSEREVENT_H_
#define LOGINUSEREVENT_H_

#include "EventHandler.h"

class LoginUserEvent: public EventHandler {
public:
	LoginUserEvent();
	LoginUserEvent(struct mg_connection*, struct http_message*);
	~LoginUserEvent();
	void handle(Manager*);

protected:
	bool validateInput();

};

#endif /* LOGINUSEREVENT_H_ */