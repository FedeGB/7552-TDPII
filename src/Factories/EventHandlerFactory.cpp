#include "EventHandlerFactory.h"
#include "../Resources/Logger.h"

EventHandlerFactory::EventHandlerFactory() {

}

EventHandlerFactory::~EventHandlerFactory() {

}

EventHandler* EventHandlerFactory::getEventHandler(struct mg_connection* nc, struct http_message* hm) {
	EventHandler* handler = NULL;
	if (mg_vcmp(&hm->uri, "/users/create") == 0) {
		LoggerManager::getInstance()->log(LoggerManager::logInfo, " /users/create Request Received");
		handler = new CreateUserEvent(nc, hm);
	} else if(mg_vcmp(&hm->uri, "/users/login") == 0) {
		LoggerManager::getInstance()->log(LoggerManager::logInfo, "/users/login Request Received");
		handler = new LoginUserEvent(nc, hm);
	} else if(mg_vcmp(&hm->uri, "/users/get") == 0) {
		LoggerManager::getInstance()->log(LoggerManager::logInfo, "/users/get Request Received");
		handler = new GetUserDataEvent(nc, hm);
	}else if(mg_vcmp(&hm->uri, "/users/delete") == 0) {
		LoggerManager::getInstance()->log(LoggerManager::logInfo, "/users/delete Request Received");
		handler = new DeleteUserEvent(nc, hm);
	} else if(mg_vcmp(&hm->uri, "/users/like") == 0) {
		LoggerManager::getInstance()->log(LoggerManager::logInfo, "/users/like Request Received");
		handler = new SaveUserLike(nc, hm);
	} else if(mg_vcmp(&hm->uri, "/users/getMatches") == 0) {
		LoggerManager::getInstance()->log(LoggerManager::logInfo, "/users/getMatches Request Received");
		handler = new GetUserMatches(nc, hm);
	} else if(mg_vcmp(&hm->uri, "/conversations/get") == 0) {
		LoggerManager::getInstance()->log(LoggerManager::logInfo, "/conversations/get Request Received");
		handler = new GetConversationEvent(nc, hm);
	} else if(mg_vcmp(&hm->uri, "/message/save") == 0) {
		LoggerManager::getInstance()->log(LoggerManager::logInfo, "/message/save Request Received");
		handler = new SaveMessageEvent(nc, hm);
	} else {
		LoggerManager::getInstance()->log(LoggerManager::logError, " Handler not Allow");
		handler = new NotAllowedEvent(nc, hm);
	}
	return handler;
}
