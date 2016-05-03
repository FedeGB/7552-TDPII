#include <gtest/gtest.h>
#include "../SharedClient/SharedManager.h"
#include "json/json.h"


TEST(SharedGetUser,TestGetUsers) {
	SharedManager* sManager = new SharedManager();
	const Json::Value& users = sManager->getUsers();
	Json::ValueConstIterator it = users.begin();
	int max = 3;
	int act = 0;
	while(it != users.end() && act < max) {
	    const Json::Value& user = *it;
		EXPECT_STRNE(user.get("id", "").asString().c_str(), "");
		it++;
		act++;
	}
	delete sManager;
}

TEST(SharedGetUser,TestGetSpecificUser) {
	SharedManager* sManager = new SharedManager();
	Json::Value user = sManager->getUser("1");
	delete sManager;
	EXPECT_STREQ(user.get("id", "").asString().c_str(), "1");
	EXPECT_STREQ(user.get("name", "").asString().c_str(), "Janeth Doe III");
	EXPECT_STREQ(user.get("alias", "").asString().c_str(), "janedoe");
}

TEST(SharedGetUser, TestPostUser) {
	// SharedManager* sManager = new SharedManager();
	// User* user = new User("username");
	// bool status = sManager->postUser(user);
	// delete user;
	// delete sManager;
	// ASSERT_TRUE(status);
}