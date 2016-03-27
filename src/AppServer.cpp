//============================================================================
// Name        : AppServer.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include <Server/RestServer.h>
#include <Server/ApplicationServerConnection.h>
#include <Server/SharedServerConnection.h>

#include <Server/HttpRequestHandler.h>

int main() {
	std::cout<<"Start"<<std::endl;

	ApplicationServerConnection appServerConnection;
	SharedServerConnection sharedServerConnection;
	RestServer restServer;
	restServer.setApplicationServer(&appServerConnection);
	restServer.setSharedServer(&sharedServerConnection);
	restServer.start();
	std::cout<<"End"<<std::endl;

}
