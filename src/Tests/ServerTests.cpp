#include <gtest/gtest.h>
#include "../Server.h"


TEST(ServerTests, ManagerGetterTest) {
	Server* serv = new Server();
	Manager* manager = serv->getManager();
	ASSERT_TRUE(manager != NULL);
	delete serv;
}

TEST(ServerTests, SimpleActionsServer) {
	Server* serv = new Server();
	ASSERT_TRUE(!serv->isRunning());
	serv->init();
	ASSERT_TRUE(serv->isRunning());
	serv->uninit();
	ASSERT_TRUE(!serv->isRunning());
	delete serv;
}