#include "EventHandlerFactory.h"
#include "../Resources/Logger.h"

EventHandlerFactory::EventHandlerFactory() {

}

EventHandlerFactory::~EventHandlerFactory() {

}

static int has_prefix(const struct mg_str *uri, const struct mg_str *prefix) {
	return uri->len > prefix->len && memcmp(uri->p, prefix->p, prefix->len) == 0;
}

string getParameter(string url){
	url = url.substr(1, url.length());
	string delimiter1 = "/";
	int positionSpace = url.find(" ");
	int positionSlash = url.find("/");
	int closer = positionSpace;
	if(positionSpace > positionSlash){
		closer = positionSlash;
	}
	int positionDelimiter = url.find(delimiter1);
	string token = url.substr(positionDelimiter, positionSpace-positionDelimiter);
	token = token.substr(1);
	return token;
}

EventHandler* EventHandlerFactory::getEventHandler(struct mg_connection* nc, struct http_message* hm) {
	EventHandler* handler = NULL;
	static const struct mg_str usersPrefix = MG_MK_STR("/users");
	static const struct mg_str matchesPrefix = MG_MK_STR("/matches");

	if(mg_vcmp(&hm->uri, "/users/login") == 0) {
		LoggerManager::getInstance()->log(LoggerManager::logInfo, "/users/login Request Received");
		handler = new LoginUserEvent(nc, hm);
	//} else if(mg_vcmp(&hm->uri, "/users") == 0) {
	} else if(has_prefix(&hm->uri, &usersPrefix)) { // /users
		string url = hm->uri.p;
		string parameter = getParameter(hm->uri.p);
		if(mg_vcmp(&hm->method, "GET") == 0){ // GET
			if(parameter == "") { // GET all users
				LoggerManager::getInstance()->log(LoggerManager::logInfo, " /users GET all users Request Received");
				handler = new GetUsers(nc, hm);
			}else{ // GET specific USER
				string logString = "/users/" + parameter + " Request received";
				LoggerManager::getInstance()->log(LoggerManager::logInfo, logString);
				handler = new GetUserDataEvent(nc, hm, parameter);
			}
		}else if( mg_vcmp(&hm->method, "POST")) { // POST
			LoggerManager::getInstance()->log(LoggerManager::logInfo, "/users POST Request Received");
			handler = new CreateUserEvent(nc, hm);
		}
		else if( mg_vcmp(&hm->method, "PUT")) { // PUT
			LoggerManager::getInstance()->log(LoggerManager::logInfo, "/users PUT Request Received");
			handler = new UpdateUserData(nc, hm, parameter);
		}
		else if( mg_vcmp(&hm->method, "DELETE")) { // DELETE
			LoggerManager::getInstance()->log(LoggerManager::logInfo, "/users DELETE Request Received");
			handler = new DeleteUserEvent(nc, hm);
		}
		string restOfUrl = url.substr(parameter.length());

		if(getParameter(parameter) == "matches"){
			string secondParameter = getParameter(restOfUrl);
			LoggerManager::getInstance()->log(LoggerManager::logInfo, "/users/getMatches Request Received");
			handler = new GetUserMatches(nc, hm);
		}

		if(getParameter(parameter) == "like"){ // /users/.../like
			if( mg_vcmp(&hm->method, "POST")) { // new Like
				LoggerManager::getInstance()->log(LoggerManager::logInfo, "/users/like Request Received");
				handler = new SaveUserLike(nc, hm);
			}
		}

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
