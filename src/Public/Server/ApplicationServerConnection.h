/*
 * ApplicationServerConnection.h
 *
 *  Created on: 21/03/2016
 *      Author: demian
 */

#ifndef APPLICATIONSERVERCONNECTION_H_
#define APPLICATIONSERVERCONNECTION_H_

#include <Server/IServerConnection.h>
#include <mongoose/mongoose.h>
#include <Application.h>

class ApplicationServerConnection: public IServerConnection {
public:
	ApplicationServerConnection();
	virtual ~ApplicationServerConnection();

	void update(RestServer& restServer);
	void init();
	void uninit();
	void handleEvent(struct mg_connection* nc, int ev, void* ev_data);

private:
	struct mg_mgr mgr;
	struct mg_connection *nc;
};

static ApplicationServerConnection* serverConnection;

static void ev_handler(struct mg_connection* nc, int ev, void* ev_data){
	serverConnection->handleEvent(nc, ev, ev_data);
}

#endif /* APPLICATIONSERVERCONNECTION_H_ */
