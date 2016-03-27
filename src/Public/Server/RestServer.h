/*
 * RestServer.h
 *
 *  Created on: 21/03/2016
 *      Author: demian
 */

#ifndef RESTSERVER_H_
#define RESTSERVER_H_

#include <Application.h>
class IServerConnection;

class RestServer {
public:
	RestServer();
	virtual ~RestServer();

	void start();
	void stop();

	void setApplicationServer(IServerConnection* applicationServer);
	void setSharedServer(IServerConnection* sharedServer);
private:
	bool isRunning;

	IServerConnection* applicationServer;
	IServerConnection* sharedServer;

	void init();
	void uninit();

};

#endif /* RESTSERVER_H_ */
