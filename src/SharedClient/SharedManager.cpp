#include "SharedManager.h"

SharedManager::SharedManager() {

}

SharedManager::~SharedManager() {

}

Json::Value SharedManager::getUsers() {
	CurlManager* curl = new CurlManager();
	curl->setUri("users");
	Json::Value resp = curl->execute();
	delete curl;
	return resp["users"];
}

Json::Value SharedManager::getUser(std::string id) {
	CurlManager* curl = new CurlManager();
	curl->setUri("users");
	curl->addUriParameter(id);
	Json::Value resp = curl->execute();
	delete curl;
	return resp["user"];	
}

bool SharedManager::postUser(User* user) {7
	// TODO TODO TODO TODOOO
	CurlManager* curl = new CurlManager();
	curl->setUri("users");
	curl->setMethodType(curl->POST);
    curl->addParameter("alias", user->getUsername());
    curl->addParameter("name", user->getName());
    curl->addParameter("email", "a@a.com");
	Json::Value resp = curl->execute();
	if(resp.get("status", "").asString().length()) {
		return false;
	}
	delete curl;
	return true;
}