/*
 * Server.h
 *
 *  Created on: Mar 26, 2016
 *      Author: juanma
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "mongoose.h"
#include "json/json.h"

#include "User.h"
#include "Database.h"

#include <stdio.h>
#include <string.h>
#include <iostream>

class Manager;

using namespace std;


class Server {
public:
	Server();
	virtual ~Server();
	void init();
	void uninit();
	void update();
	//string readRequestHeader(mg_connection* conn, string header);
	void handleEvent(struct mg_connection* nc, int ev, void* ev_data);
	string loginUser(string, string);
	void createUser(Json::Value json);
	void handleCreateUser(struct mg_connection *nc, struct http_message *hm);
	void handleLogin(struct mg_connection*, struct http_message*);
	void setManager(Manager* mg);
	Manager* getManager();

	void respondNotAllowedMethod(struct mg_connection*);
	void respondNotFound(struct mg_connection*);

private:
	Manager* manager;
	struct mg_mgr mgr;
	struct mg_connection *nc;
	char *s_http_port;


};


static void ev_handler(struct mg_connection* nc, int ev, void* ev_data){
	Server* server = (Server*) nc->mgr->user_data;
	server->handleEvent(nc, ev, ev_data);
}
#endif /* SERVER_H_ */
