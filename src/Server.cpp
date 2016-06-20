/*
 * Server.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: juanma
 */

#include "Server.h"
#include "Resources/Logger.h"

Server::Server() {
	//this->s_http_port = "8000";
	this->manager = new Manager();
	this->eventFactory = new EventHandlerFactory();
	this->sManager = new SharedManager();
	//this->mgr.user_data = this;
}

Server::~Server() {
	  mg_mgr_free(&mgr);
	  delete manager;
	  delete eventFactory;
	  delete sManager;
}


void Server::init(){
	mg_mgr_init(&mgr, this);
	nc = mg_bind(&mgr, "8000", ev_handler);
	mg_set_protocol_http_websocket(nc);
}


void Server::uninit(){
	mg_mgr_free(&mgr);
}

void Server::update(){
	mg_mgr_poll(&mgr, 1000);
}


void Server::handleEvent(struct mg_connection* nc, int ev, void* ev_data){
		struct http_message *hm = (struct http_message *) ev_data;
		switch(ev) {
			case MG_EV_HTTP_REQUEST: {
				printf("Llego un request \n");
				LoggerManager::getInstance()->log(LoggerManager::logInfo, " Request arrived to the Server ");
				LoggerManager::getInstance()->log(LoggerManager::logDebug, "Request Body: " + std::string(hm->body.p));
				EventHandler* ehandler = eventFactory->getEventHandler(nc, hm);
				ehandler->handle(this->manager, this->sManager);
				LoggerManager::getInstance()->log(LoggerManager::logInfo, " Request processed");
				printf("Procesado un request \n");
				break;
			}
			default:
				break;
		}
}

void Server::setManager(Manager* mg){
	manager = mg;
}

Manager* Server::getManager(){
	return manager;
}

void Server::setSharedManager(SharedManager* sm) {
	this->sManager = sm;
}


SharedManager* Server::getSharedManager() {
	return this->sManager;
}


void Server::statisticCalculations() {
	vector<Json::Value> users = this->manager->getAllUsers();
	int total = users.size();
	User* actualUser = NULL;
	int onePercent = total/100;
	if(!onePercent) onePercent = 1;
	int i = 0;
	// while(i < total) {
	// 	actualUser = users.at(i);
	// 	int actualLikes = actualUser->getLikesReceived();
	// 	i++;
	// }
}