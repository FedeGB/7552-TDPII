/*
 * IServer.h
 *
 *  Created on: 21/03/2016
 *      Author: demian
 */

#ifndef ISERVER_H_
#define ISERVER_H_

class RestServer;

class IServerConnection {
public:
	virtual void init() = 0;
	virtual void uninit() = 0;
	virtual void update(RestServer& restServer) = 0;
	virtual ~IServerConnection() {};

};

#endif /* ISERVER_H_ */
