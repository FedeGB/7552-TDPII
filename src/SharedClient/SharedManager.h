#ifndef SHAREDMANAGER_H_
#define SHAREDMANAGER_H_

#include "CurlManager.h"

class SharedManager {
public:
	SharedManager();
	virtual ~SharedManager();

	Json::Value getUsers();

};

#endif /*SHAREDMANAGER_H_*/