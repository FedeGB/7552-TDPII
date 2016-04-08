#include <iostream>
#include <gtest/gtest.h>
#include "Server.h"

int main(int argc, char *argv[]){


//	Server* serv = new Server();
//	serv->init();
//	printf("Server iniciado \n");
//
//	for (;;) {
//		serv->update();
//	}
//	std::cout<<"End"<<std::endl;
//
//	return 0;

	std::cout<<"Estructura base del proyecto!"<<std::endl;
	::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
