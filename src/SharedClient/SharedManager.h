#ifndef SHAREDMANAGER_H_
#define SHAREDMANAGER_H_

#include "CurlManager.h"
#include "../User.h"

class SharedManager {
public:
	SharedManager();
	virtual ~SharedManager();

	Json::Value getUsers();
	Json::Value getUser(std::string);
	bool postUser(User*);
};

#endif /*SHAREDMANAGER_H_*/