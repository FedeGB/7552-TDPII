#include <iostream>
#include <gtest/gtest.h>
#include "Server.h"
#include "Resources/Logger.h"
#include <csignal>


Server* serv = NULL;

void signalHandler( int signum )
{
	if(serv) {
		serv->uninit();
		LoggerManager::getInstance()->log(LoggerManager::logInfo, "Server Closed");
		delete serv;
		std::cout << "Signal (" << signum << ") received. Closing Server.." << std::endl;
	}
	exit(signum);
}

int main(int argc, char *argv[]){

	LoggerManager::getInstance()->log(LoggerManager::logInfo, "Server Started");
	signal(SIGINT, signalHandler);
	serv = new Server();
	if(argc > 1) {
		serv->fillWithSharedUsers();
	}
	serv->init();
	printf("Server iniciado \n");

	for (;;) {
		serv->update();
	}

	return 0;
}
