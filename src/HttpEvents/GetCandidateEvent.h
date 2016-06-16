#ifndef __GETCANDIDATEEVENT_H_
#define __GETCANDIDATEEVENT_H_

#include "EventHandler.h"
#include "../Utils.h"
#include <map>
#include <algorithm>


class GetCandidateEvent: public EventHandler {
public:
	GetCandidateEvent();
	GetCandidateEvent(struct mg_connection*, struct http_message*, std::string);
	virtual ~GetCandidateEvent();
	void handle(Manager*, SharedManager*);

protected:
	bool validateInput();
	string parameter;
};


#endif /* __GETCANDIDATEEVENT_H_ */