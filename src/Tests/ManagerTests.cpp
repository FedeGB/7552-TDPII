
#include <gtest/gtest.h>
#include "../Manager.h"

TEST(ManagerTests, GetterManagerTest) {
    Manager* manager = new Manager();
    ASSERT_TRUE(manager->getDatabase() != NULL);
    delete manager;
    manager = NULL;
}


TEST(ManagerTests, CreateAndDeleteUserTest) {
	Manager* manager = new Manager();
	srand (time(NULL));
	User* user = new User("user" + std::to_string(rand() % 1000));
	bool result = manager->createUser(user->getJsonString());
	ASSERT_TRUE(result);
	User* userGet = manager->getUser(user->getUsername());
	ASSERT_EQ(user->getUsername(), userGet->getUsername());
	result = manager->deleteUser(user->getUsername());
	ASSERT_TRUE(result);	
	delete user;
	delete userGet;
	delete manager;
	manager = NULL;
	userGet = NULL;
	user = NULL;
}

TEST(ManagerTests, CreateUpdateAndDeleteUserTest) {
	Manager* manager = new Manager();
	srand (time(NULL));
	User* user = new User("user" + std::to_string(rand() % 2000));
	bool result = manager->createUser(user->getJsonString());
	ASSERT_TRUE(result);
	User* userGet = manager->getUser(user->getUsername());
	ASSERT_EQ(user->getUsername(), userGet->getUsername());
	delete userGet;
	userGet = NULL;
	Json::Value updates;
	srand (time(NULL));
	updates["username"] = "user" + std::to_string(rand() % 555);
	user->updateWithJson(updates);
	result = manager->updateUser(user);
	ASSERT_TRUE(result);
	userGet = manager->getUser(updates.get("username", "").asString());
	ASSERT_EQ(updates.get("username", "").asString(), userGet->getUsername());
	result = manager->deleteUser(userGet->getUsername());
	ASSERT_TRUE(result);	
	delete user;
	delete userGet;
	delete manager;
	manager = NULL;
	user = NULL;
	userGet = NULL;
}

TEST(ManagerTests, SaveAndDeleteLikeTest) {
	Manager* manager = new Manager();
	Json::Value u1;
	srand (time(NULL));
	u1["username"] = "user" + std::to_string(rand() % 55555);
	u1["password"] = "123";
	Json::Value u2;
	srand (time(NULL));
	u2["username"] = "user" + std::to_string(rand() % 77777);
	u2["password"] = "123";
	Json::FastWriter fast;
	std::string jsonu1 = fast.write(u1);
	manager->createUser(jsonu1);
	std::string jsonu2 = fast.write(u2);
	manager->createUser(jsonu2);
	User* user1 = manager->getUser(u1.get("username", "").asString());
	User* user2 = manager->getUser(u2.get("username", "").asString());
	Like* like = new Like(user1, user2, true);
	bool res = manager->saveLike(like->getJsonString());
	ASSERT_TRUE(res);
	Like* likeGet = manager->getLike(user1->getUsername() + user2->getUsername());
	ASSERT_TRUE(likeGet != NULL);
	res = manager->deleteLike(user1->getUsername(), user2->getUsername());
	ASSERT_TRUE(res);
	delete like;
	delete likeGet;
	delete user1;
	delete user2;
	delete manager;
	manager = NULL;
}