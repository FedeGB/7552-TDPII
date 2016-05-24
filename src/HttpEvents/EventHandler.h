#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include "../mongoose.h"
#include "../json/json.h"
#include "../Manager.h"
#include "../SharedClient/SharedManager.h"
#include "../Message.h"
#include <string>

class EventHandler {
public:
	EventHandler(struct mg_connection*, struct http_message*);
	EventHandler();
	virtual ~EventHandler();
	virtual void handle(Manager*, SharedManager*);

protected:
	std::string methodType;
	struct mg_connection* nc;
	struct http_message* hm;

	virtual bool validateInput();
	virtual void respondNotAllowedMethod();
	virtual void respondNotFound();
	virtual void response(int, std::string, Json::Value);
};


#endif /* EVENTHANDLER_H_ */