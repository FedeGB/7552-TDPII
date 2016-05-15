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

long SharedManager::postUser(Json::Value user) {
	LoggerManager::getInstance()->log(LoggerManager::logInfo, "Post request of user " + user.get("alias", "").asString());
	CurlManager* curl = new CurlManager();
	curl->setUri("users");
	curl->setMethodType(curl->POST);
	curl->addHeader("content-type: application/json");
	Json::Value userReq = Json::Value();
	userReq["alias"] = user.isMember("alias") ? user.get("alias", "").asString() : user.get("name", "").asString();
	userReq["name"] = user.get("name", "").asString();
	userReq["email"] = user.get("email", "").asString();
	userReq["sex"] = user.isMember("sex") ? user.get("sex", "").asString() : "";
	if(user.isMember("photoProfile")) {
		userReq["photoProfile"] = user.get("photoProfile", "").asString();
	} else {
		Json::Value photo; // null value
		userReq["photoProfile"] = photo;
	}
    if(user.isMember("location")) {
    	userReq["location"] = user.get("location", "");	
    } else {
	    Json::Value location = Json::Value();
	    location["longitude"] = 0;
	    location["latitude"] = 0;
		userReq["location"] = location;
    }
    if(user.isMember("interests")) {
    	userReq["interests"] = user.get("interests", "");
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
	LoggerManager::getInstance()->log(LoggerManager::logInfo, "Post request of user " + user.get("alias", "").asString()
		+ ". Response status: " + resp.get("status", "").asString());
	if(resp.isMember("error", "")) {
		std::string logMessage = "Post request of user " + user.get("alias", "").asString()
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