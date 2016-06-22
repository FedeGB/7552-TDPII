#include <iostream>
#include <gtest/gtest.h>
#include "Server.h"
#include "Resources/Logger.h"
#include <csignal>


Server* serv = NULL;

void signalHandler( int signum )
{
	std::cout << "Signal (" << signum << ") received. Closing Server.." << std::endl;
	if(serv) {
		serv->uninit();
		LoggerManager::getInstance()->log(LoggerManager::logInfo, "Server Closed");
		delete serv;
	}
	exit(signum);
}

int main(int argc, char *argv[]){

	LoggerManager::getInstance()->log(LoggerManager::logInfo, "Server Started");
	signal(SIGINT, signalHandler);
	serv = new Server();
	serv->init();
	printf("Server iniciado \n");

	for (;;) {
		serv->update();
	}

	return 0;
}
