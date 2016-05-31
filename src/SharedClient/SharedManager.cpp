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
	if(!user.isMember("alias") && user.isMember("name")) {
		user["alias"] = user.get("name", "").asString();
	}
	if(!user.isMember("photoProfile")) {
		Json::Value photo; // null value
		user["photoProfile"] = photo;
	}
    if(!user.isMember("location")) {
	    Json::Value location = Json::Value();
	    location["longitude"] = 0;
	    location["latitude"] = 0;
		user["location"] = location;
    }
    if(!user.isMember("interests")) {
    	Json::Value interests = Json::Value(Json::arrayValue);
	    Json::Value defInterest = Json::Value();
	    defInterest["category"] = "sex";
	    defInterest["value"] = user.get("sex", "").asString().compare("M") == 0 ? "Woman" : "Man";
	    interests[0] = defInterest;
		user["interests"] = interests;
    }
    //std::cout << user << std::endl;
	curl->addJsonParameter("user", user);
	Json::Value resp = curl->execute();
	LoggerManager::getInstance()->log(LoggerManager::logInfo, "Post request of user " + user.get("alias", "").asString()
		+ ". Response status: " + resp.get("status", "").asString());
	delete curl;
	if(resp.isMember("error", "")) {
		std::string logMessage = "Post request of user " + user.get("alias", "").asString()
		+ ". Response status: " + resp.get("status", "").asString() 
		+ ". With error: " + resp.get("error", "").asString();
		LoggerManager::getInstance()->log(LoggerManager::logInfo, logMessage);
		return 0;
	}
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

int SharedManager::putUser(Json::Value userWithDiffs) {
	LoggerManager::getInstance()->log(LoggerManager::logInfo, "Put request of user " + userWithDiffs.get("id", "").asString());
	CurlManager* curl = new CurlManager();
	curl->setUri("users");
	curl->setMethodType(curl->PUT);
	curl->addHeader("content-type: application/json");
	curl->addUriParameter(userWithDiffs.get("id", "").asString());
	// TODO: Habria que ver de hacer este tipo de gets para mas usuarios y ver de validar con el Shared
	// Al que estamos conectados ahora, para ver si es valido el PUT sobre este usuario
	if(!userWithDiffs.isMember("alias") && userWithDiffs.isMember("name")) {
		userWithDiffs["alias"] = userWithDiffs.get("name", "").asString();
	}
	if(!userWithDiffs.isMember("interests")) {
		Json::Value sharedUser = this->getUser(userWithDiffs.get("id", "").asString());
		userWithDiffs["interests"] = sharedUser.get("interests", "");
    }
	curl->addJsonParameter("user", userWithDiffs);
	Json::Value resp = curl->execute();
	delete curl;
	LoggerManager::getInstance()->log(LoggerManager::logInfo, "Put request of user " + userWithDiffs.get("id", "").asString()
		+ ". Response status: " + resp.get("status", "").asString());
	if(resp.isMember("error", "")) {
		std::string logMessage = "Put request of user " + userWithDiffs.get("id", "").asString()
		+ ". Response status: " + resp.get("status", "").asString() 
		+ ". With error: " + resp.get("error", "").asString();
		LoggerManager::getInstance()->log(LoggerManager::logInfo, logMessage);
		return 0;
	}
	return (long)std::stol(resp.get("id", 0).asString());
}

int SharedManager::putUserPhoto(Json::Value data) {
	LoggerManager::getInstance()->log(LoggerManager::logInfo, "Put request of user photo " + data.get("id", "").asString());
	CurlManager* curl = new CurlManager();
	curl->setUri("users");
	curl->setMethodType(curl->PUT);
	curl->addHeader("content-type: application/json");
	curl->addUriParameter(data.get("id", "").asString() + "/photo");
	curl->addUniqueParameter("photo", data.get("photo","").asString());
	Json::Value resp = curl->execute();
	delete curl;
	LoggerManager::getInstance()->log(LoggerManager::logInfo, "Put request of user photo " + data.get("id", "").asString()
		+ ". Response status: " + resp.get("status", "").asString());
	if(resp.isMember("error", "")) {
		std::string logMessage = "Put request of user photo " + data.get("id", "").asString()
		+ ". Response status: " + resp.get("status", "").asString() 
		+ ". With error: " + resp.get("error", "").asString();
		LoggerManager::getInstance()->log(LoggerManager::logInfo, logMessage);
		return 0;
	}
	return (long)std::stol(resp.get("id", 0).asString());
}

Json::Value SharedManager::getInterests() {
	CurlManager* curl = new CurlManager();
	curl->setUri("interests");
	Json::Value resp = curl->execute();
	delete curl;
	return resp["interests"];
}

bool SharedManager::postInterest(Json::Value interest) {
	LoggerManager::getInstance()->log(LoggerManager::logInfo, 
		"Post request of interest " + interest.get("category", "").asString()
		+ " - " + interest.get("value", "").asString());
	CurlManager* curl = new CurlManager();
	curl->setUri("interests");
	curl->setMethodType(curl->POST);
	curl->addHeader("content-type: application/json");
	curl->addJsonParameter("interest", interest);
	Json::Value resp = curl->execute();
	LoggerManager::getInstance()->log(LoggerManager::logInfo,
	 	"Post request of interest " + interest.get("category", "").asString()
		+ " - " + interest.get("value", "").asString()
		+ ". Response status: " + resp.get("status", "").asString());
	delete curl;
	if(resp.isMember("error", "")) {
		std::string logMessage = "Post request of interest " + interest.get("category", "").asString()
		+ " - " + interest.get("value", "").asString()
		+ ". Response status: " + resp.get("status", "").asString() 
		+ ". With error: " + resp.get("error", "").asString();
		LoggerManager::getInstance()->log(LoggerManager::logInfo, logMessage);
		return false;
	}
	return true;
}