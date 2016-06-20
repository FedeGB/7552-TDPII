/*
 * Server.h
 *
 *  Created on: Mar 26, 2016
 *      Author: juanma
 */

#ifndef SERVER_H_
#define SERVER_H_

//#include "mongoose.h"
//#include "json/json.h"

#include "User.h"
#include "Factories/EventHandlerFactory.h"
#include "Database.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <thread>
#include <unistd.h>

class Manager;

using namespace std;

class Server {
public:
	Server();
	virtual ~Server();
	void init();
	void uninit();
	void update();
	void handleEvent(struct mg_connection* nc, int ev, void* ev_data);
	void setManager(Manager* mg);
	Manager* getManager();
	string readRequestHeader(mg_connection* conn, string header);
	void statisticCalculations();

	void setSharedManager(SharedManager*);
	SharedManager* getSharedManager();

private:
	Manager* manager;
	SharedManager* sManager;
	struct mg_mgr mgr;
	struct mg_connection *nc;
	char *s_http_port;
	EventHandlerFactory* eventFactory;
	std::thread statistics;
	time_t lastStatisticRun;
	bool running;

};


static void ev_handler(struct mg_connection* nc, int ev, void* ev_data){
	Server* server = (Server*) nc->mgr->user_data;
	server->handleEvent(nc, ev, ev_data);
}

bool orderByLikesDesc(Json::Value, Json::Value);

#endif /* SERVER_H_ */
