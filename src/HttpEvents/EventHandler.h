#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include "mongoose.h"
#include "json/json.h"

class EventHandler {
public:
	EventHandler(struct mg_connection*, struct http_message*);
	virtual ~EventHandler();
	virtual void handle();

protected:
	string methodType;
	struct mg_connection* nc;
	struct http_message* hm;

	virtual bool validateInput();
	virtual void respondNotAllowedMethod();
	virtual void respondNotFound();
	virtual void response(int, string, Json::Value);
};


#endif /* EVENTHANDLER_H_ */