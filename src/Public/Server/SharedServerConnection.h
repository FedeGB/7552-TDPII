/*
 * SharedServerConnection.h
 *
 *  Created on: 21/03/2016
 *      Author: demian
 */

#ifndef SHAREDSERVERCONNECTION_H_
#define SHAREDSERVERCONNECTION_H_

#include <Server/IServerConnection.h>

class SharedServerConnection : public IServerConnection {
public:
	SharedServerConnection();
	virtual ~SharedServerConnection();

	void init();
	void uninit();
	void update(RestServer& restServer);
};

#endif /* SHAREDSERVERCONNECTION_H_ */
