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

long SharedManager::postUser(User* user, Json::Value extra) {
	LoggerManager::getInstance()->log(LoggerManager::logInfo, "Post request of user " + user->getUsername());
	CurlManager* curl = new CurlManager();
	curl->setUri("users");
	curl->setMethodType(curl->POST);
	curl->addHeader("content-type: application/json");
	Json::Value userReq = Json::Value();
	userReq["alias"] = extra.isMember("alias") ? extra.get("alias", "").asString() : user->getUsername();
	userReq["name"] = user->getName();
	userReq["email"] = user->getEmail();
	userReq["sex"] = extra.isMember("sex") ? extra.get("sex", "").asString() : "";
	if(extra.isMember("photoProfile")) {
		userReq["photoProfile"] = extra.get("photoProfile", "").asUInt();
	} else {
		Json::Value photo; // null value
		userReq["photoProfile"] = photo;
	}
    if(extra.isMember("location")) {
    	userReq["location"] = extra.get("location", "");	
    } else {
	    Json::Value location = Json::Value();
	    location["longitude"] = user->getLongitude();
	    location["latitude"] = user->getLatitude();
		userReq["location"] = location;
    }
    if(extra.isMember("interests")) {
    	userReq["interests"] = extra.get("interests", "");
    } else{
    	Json::Value interests = Json::Value(Json::arrayValue);
	    Json::Value defInterest = Json::Value();
	    defInterest["category"] = "sex";
	    defInterest["value"] = userReq.get("sex", "").asString().compare("M") == 0 ? "Woman" : "Man";
	    interests[0] = defInterest;
		userReq["interests"] = interests;
    }
	curl->addJsonParameter("user", userReq);
	Json::Value resp = curl->execute();
	LoggerManager::getInstance()->log(LoggerManager::logInfo, "Post request of user " + user->getUsername()
		+ ". Response status: " + resp.get("status", "").asString());
	if(resp.isMember("error", "")) {
		std::string logMessage = "Post request of user " + user->getUsername()
		+ ". Response status: " + resp.get("status", "").asString() 
		+ ". With error: " + resp.get("error", "").asString();
		LoggerManager::getInstance()->log(LoggerManager::logInfo, logMessage);
		delete curl;
		return 0;
	}
	delete curl;
	return (long)std::stol(resp.get("id", 0).asString());
}

bool SharedManager::deleteUser(int id) {
	LoggerManager::getInstance()->log(LoggerManager::logInfo, "Delete request of user " + std::to_string(id));
	CurlManager* curl = new CurlManager();
	curl->setUri("users");
	curl->setMethodType(curl->DELETE);
	curl->addUriParameter(std::to_string(id));
	Json::Value resp = curl->execute();
	LoggerManager::getInstance()->log(LoggerManager::logInfo, "Delete request of user " + std::to_string(id
)		+ ". Response status: " + resp.get("status", "").asString());
	delete curl;
	if(resp.isMember("error", "")) {
		std::string logMessage = "Delete request of user " + std::to_string(id)
		+ ". Response status: " + resp.get("status", "").asString() 
		+ ". With error: " + resp.get("error", "").asString();
		LoggerManager::getInstance()->log(LoggerManager::logInfo, logMessage);
		return false;
	}
	if(resp.get("message", "").asString().compare("OK") == 0) {
		std::string logMessage = "Delete request of user " + std::to_string(id)
		+ ". Was deleted.";
		LoggerManager::getInstance()->log(LoggerManager::logInfo, logMessage);
		return true;
	} else {
		std::string logMessage = "Delete request of user " + std::to_string(id)
		+ ". Was not deleted.";
		LoggerManager::getInstance()->log(LoggerManager::logInfo, logMessage);
		return false;
	}
}