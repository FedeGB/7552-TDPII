#include "SharedManager.h"


SharedManager::SharedManager() {
	this->url = "http://tp-7552-g05-sharedserver.herokuapp.com";
}

SharedManager::~SharedManager() {

}

Json::Value SharedManager::getUser(std::string id) {
	
    return Json::Value();
}