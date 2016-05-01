#ifndef SHAREDMANAGER_H_
#define SHAREDMANAGER_H_

#include <string>
#include <curl/curl.h>
#include "json/json.h"



class SharedManager {

private:
	std::string url;

public:
	SharedManager();
	virtual ~SharedManager();

	Json::Value getUser(std::string id);

};

#endif /*SHAREDMANAGER_H_*/