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

bool SharedManager::postUser(User* user) {
	LoggerManager::getInstance()->log(LoggerManager::logInfo, "Post request of user " + user->getUsername());
	CurlManager* curl = new CurlManager();
	curl->setUri("users");
	curl->setMethodType(curl->POST);
	Json::Value userReq = Json::Value();
	userReq["alias"] = user->getUsername();
	userReq["name"] = "hello there";
	userReq["email"] = "aasda@sdasa.com";
	userReq["sex"] = "M";
	Json::Value photo;
	userReq["photoProfile"] = photo;
    Json::Value location = Json::Value();
    location["longitude"] = 32.1;
    location["latitude"] = 23.2;
	userReq["location"] = location;
    Json::Value interests = Json::Value(Json::arrayValue);
    Json::Value rock = Json::Value();
    rock["category"] = "music/band";
    rock["value"] = "radiohead";
    interests[0] = rock;
	userReq["interests"] = interests;
	curl->addHeader("content-type: application/json");
	curl->addJsonParameter("user", userReq);
    // curl->addUniqueParameter(, );
    // curl->addUniqueParameter(, );
    // curl->addUniqueParameter(, );
    // curl->addUniqueParameter(, );
    // curl->addUniqueParameter(, "");
    // curl->addJsonParameter("location", location);
    // curl->addJsonParameter("interests-", interests);
	Json::Value resp = curl->execute();
    LoggerManager::getInstance()->log(LoggerManager::logDebug, resp.get("status", "").asString());
	LoggerManager::getInstance()->log(LoggerManager::logInfo, "Post request of user " + user->getUsername()
		+ ". Response status: " + resp.get("status", "").asString());
	std::cout << "Status " << resp.get("status", "").asString() << std::endl;
	if(resp.get("status", "").asString().length()) {
		delete curl;
		return false;
	}
	delete curl;
	return true;
}