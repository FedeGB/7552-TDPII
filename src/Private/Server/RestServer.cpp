/*
 * RestServer.cpp
 *
 *  Created on: 21/03/2016
 *      Author: demian
 */

#include <Server/RestServer.h>
#include <Server/IServerConnection.h>

RestServer::RestServer() {
	this->isRunning = false;
	this->sharedServer = nullPtr;
	this->applicationServer = nullPtr;
}

RestServer::~RestServer() {
	// TODO Auto-generated destructor stub
}

void RestServer::start() {
	this->isRunning = true;

	this->init();

	while(this->isRunning){
		this->applicationServer->update(*this);
		this->sharedServer->update(*this);
	}

	this->uninit();
}

void RestServer::stop() {
	this->isRunning = false;

}

void RestServer::setApplicationServer(IServerConnection* applicationServer){
	this->applicationServer = applicationServer;
}

void RestServer::setSharedServer(IServerConnection* sharedServer){
	this->sharedServer = sharedServer;
}

void RestServer::init(){
	if(!this->sharedServer || !this->applicationServer){
		//TODO: LOG -> NO SHARED AND APLICATION SERVER DEFINED!
		return;
	}

	this->applicationServer->init();
	this->sharedServer->init();
}

void RestServer::uninit(){
		this->applicationServer->uninit();
		this->sharedServer->uninit();
}

