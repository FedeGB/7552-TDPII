#include <gtest/gtest.h>
#include "../SharedClient/SharedManager.h"
#include "../json/json.h"
#include <time.h>


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

void get_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

	srand(time(NULL));
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

TEST(SharedGetUser, TestPostAndDeleteUser) {
	SharedManager* sManager = new SharedManager();
	char* username = new char[10]();
	get_random(username, 9);
	User* user = new User(std::string(username));
	char* name = new char[10]();
	get_random(name, 9);
	user->setName(std::string(name));
	char* email = new char[10]();
	get_random(email, 9);
	user->setEmail(std::string(email));
	Json::Value extra = Json::Value();
	extra["sex"] = "M";
	long id = sManager->postUser(user, extra);
	delete[] username;
	delete[] name;
	delete[] email;
	delete user;
	ASSERT_TRUE(id != 0);
	bool wasDeleted = sManager->deleteUser((int)id);
	delete sManager;
	ASSERT_TRUE(wasDeleted);
}