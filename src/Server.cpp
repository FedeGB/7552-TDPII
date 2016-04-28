/*
 * Server.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: juanma
 */

#include "Server.h"
#include "Resources/Logger.h"
#include "Manager.h"
#include "json/json.h"

//static struct mg_serve_http_opts s_http_server_opts;

Server::Server() {
	//this->s_http_port = "8000";
	this->manager = new Manager();
	this->eventFactory = new EventHandlerFactory();
	//this->mgr.user_data = this;
}

Server::~Server() {
	  mg_mgr_free(&mgr);
	  delete manager;
	  delete eventFactory;
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


/*
string Server::readRequestHeader(mg_connection* conn, string header){
	const char* headerPointer = mg_get_header(conn, header.c_str());
	string h = "";

	if (headerPointer){
		string h1(headerPointer);
		h = h1;
	}

	return h;
}
*/
//
void Server::handleEvent(struct mg_connection* nc, int ev, void* ev_data){
		struct http_message *hm = (struct http_message *) ev_data;
		switch(ev) {
			case MG_EV_HTTP_REQUEST: {
				printf("Llego un request \n");
				LoggerManager::getInstance()->log(LoggerManager::logInfo, " Request arrived to the Server ");
				EventHandler* ehandler = eventFactory->getEventHandler(nc, hm);
				ehandler->handle(this->manager);
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