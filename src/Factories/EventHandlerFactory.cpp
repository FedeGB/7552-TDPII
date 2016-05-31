#include "EventHandlerFactory.h"
#include "../Resources/Logger.h"

EventHandlerFactory::EventHandlerFactory() {

}

EventHandlerFactory::~EventHandlerFactory() {

}

static int has_prefix(const struct mg_str *uri, const struct mg_str *prefix) {
	return uri->len >= prefix->len && memcmp(uri->p, prefix->p, prefix->len) == 0;
}

string getParameter(string url){
	url = url.substr(1, url.length());
	string delimiter1 = "/";
	int positionSpace = url.find(" ");
	int positionSlash = url.find("/");
	if(positionSpace < positionSlash && positionSpace > 0){
		return "";
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
	static const struct mg_str messagesPrefix = MG_MK_STR("/messages");
	static const struct mg_str conversationPrefix = MG_MK_STR("/conversations");
	static const struct mg_str likesPrefix = MG_MK_STR("/likes");
	static const struct mg_str candidatePrefix = MG_MK_STR("/candidate");
	static const struct mg_str loginPrefix = MG_MK_STR("/users/login");
	{
		
	};


	if(has_prefix(&hm->uri, &loginPrefix)) {
		LoggerManager::getInstance()->log(LoggerManager::logInfo, "/users/login Request Received");
		handler = new LoginUserEvent(nc, hm);
	}
	else if(has_prefix(&hm->uri, &usersPrefix)) { // /users
		string url = hm->uri.p;
		string parameter = getParameter(hm->uri.p);
		if(mg_vcmp(&hm->method, "GET") == 0){ // GET
			if(parameter == "") { // GET all users
				LoggerManager::getInstance()->log(LoggerManager::logInfo, " /users GET all users Request Received");
				handler = new GetUsers(nc, hm);
			}else if(getParameter(parameter) == "matches"){
				LoggerManager::getInstance()->log(LoggerManager::logInfo, "/users/getMatches Request Received");
				handler = new GetUserMatches(nc, hm);
			}
			else{ // GET specific USER
				string logString = "/users/" + parameter + " Request received";
				LoggerManager::getInstance()->log(LoggerManager::logInfo, logString);
				handler = new GetUserDataEvent(nc, hm, parameter);
			}
		}else if( mg_vcmp(&hm->method, "POST") == 0) { // POST
			LoggerManager::getInstance()->log(LoggerManager::logInfo, "/users POST Request Received");
			handler = new CreateUserEvent(nc, hm);
		}
		else if( mg_vcmp(&hm->method, "PUT") == 0) { // PUT
			LoggerManager::getInstance()->log(LoggerManager::logInfo, "/users PUT Request Received");
			handler = new UpdateUserData(nc, hm, parameter);
		}
		else if( mg_vcmp(&hm->method, "DELETE") == 0) { // DELETE
			LoggerManager::getInstance()->log(LoggerManager::logInfo, "/users DELETE Request Received");
			handler = new DeleteUserEvent(nc, hm);
		}
		string restOfUrl = url.substr(parameter.length());
		if(parameter.length() > 0){
			if(getParameter(parameter) == "like"){ // /users/.../like
				if( mg_vcmp(&hm->method, "POST")) { // new Like
					LoggerManager::getInstance()->log(LoggerManager::logInfo, "/users/like Request Received");
					handler = new SaveUserLike(nc, hm);
				}
			}
		}


	} else if(has_prefix(&hm->uri, &conversationPrefix)) { //    /conversations
		if (mg_vcmp(&hm->method, "GET") == 0) { // GET all conversations
			//TODO get all conversations
			LoggerManager::getInstance()->log(LoggerManager::logInfo, "/conversations Request Received");
			handler = new GetConversationEvent(nc, hm);
		}
		else if (mg_vcmp(&hm->method, "POST") == 0) { // POST create a new conversation
			//handler = new GetConversationEvent(nc, hm);
		}
		else if(mg_vcmp(&hm->method, "PUT") == 0) { // PUT modifiy a conversation
			//TODO modify conver
		}
		else if(mg_vcmp(&hm->method, "DELETE") == 0) { // DELETE a conversation
			//TODO delete a conversation
		}

	}

	else if(has_prefix(&hm->uri, &messagesPrefix)) { //    /messages
		if(mg_vcmp(&hm->method, "GET") == 0) { // GET all messages
			LoggerManager::getInstance()->log(LoggerManager::logInfo, "/messages POST Request Received");
			handler = new GetMessages(nc, hm);
		}
		if(mg_vcmp(&hm->method, "POST") == 0) { // POST create a new message
			LoggerManager::getInstance()->log(LoggerManager::logInfo, "/messages POST Request Received");
			handler = new SaveMessageEvent(nc, hm);
		}
		else if(mg_vcmp(&hm->method, "PUT") == 0) { // PUT modifiy a message
			// TODO modify message
		}
		else if(mg_vcmp(&hm->method, "DELETE") == 0) { // DELETE a message
			// TODO delete message
		}
	}

	else if(has_prefix(&hm->uri, &likesPrefix)) { //    /likes
		if(mg_vcmp(&hm->method, "GET") == 0) { // GET all messages
			//TODO get all likes
		}
		if(mg_vcmp(&hm->method, "POST") == 0) { // POST create a new message
			LoggerManager::getInstance()->log(LoggerManager::logInfo, "/likes POST Request Received");
			handler = new SaveUserLike(nc, hm);
		}
		else if(mg_vcmp(&hm->method, "PUT") == 0) { // PUT modifiy a message
			// TODO modify message
		}
		else if(mg_vcmp(&hm->method, "DELETE") == 0) { // DELETE a message
			// TODO delete message
		}
	}

	else if(has_prefix(&hm->uri, &candidatePrefix)) { // candidates
		if(mg_vcmp(&hm->method, "GET") == 0) { // GET candidates
			string parameter = getParameter(hm->uri.p);
			LoggerManager::getInstance()->log(LoggerManager::logInfo,
			 "/candidates/" + parameter + " GET Request Received");
			handler = new GetCandidateEvent(nc, hm, parameter);
		}
	}

	else {
		LoggerManager::getInstance()->log(LoggerManager::logError, " Handler not Allow");
		handler = new NotAllowedEvent(nc, hm);
	}
	return handler;
}
