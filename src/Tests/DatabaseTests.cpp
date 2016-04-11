#include <gtest/gtest.h>
#include "../User.h"
#include "../Message.h"
#include "../Database.h"





TEST(DatabaseTests,TestSaveKeyValue){
	Database* database = new Database();
	string key = "key";
	string value = "value";
	bool res = database->put(key,value);
	ASSERT_EQ(true, res);
	string aux;
	string expectedValue = database->get(key, aux);
	ASSERT_EQ(value,expectedValue);
	delete database;

}


TEST(DatabaseTests,TestSaveUser){
	Database* database = new Database();
	User* user = new User("User1");
	user->setPassword("hola");
	user->setName("Juan");
	user->setLocationX(20.0);
	user->setLocationY(40.0);
	user->setPerfilImage("URL");
	database->saveUser(user);
	ASSERT_EQ(user->getName(), database->getUser(user->getUsername())->getName());
	delete user;
	delete database;
}


TEST(DatabaseTests,TestSaveAndGetUser){
	Database* database = new Database();
	User* user = new User("User1");
	user->setPassword("hola");
	user->setName("Juan");
	user->setLocationX(20.0);
	user->setLocationY(40.0);
	user->setPerfilImage("URL");
	database->saveUser(user);
	ASSERT_EQ(user->getName(), database->getUser(user->getUsername())->getName());
	delete user;
	delete database;
}
/*
TEST(DatabaseTests,TestSaveAndGetMessage){
	Database* database = new Database();
	User* user1 = new User("User1");
	User* user2 = new User("User2");
	string data = "hola";
	Message* message = new Message(user1, user2, data);
	message->setId("1");
	database->saveMessage(message);
	ASSERT_EQ(data, database->getMessage(user1,user2, "1" ));
	delete user1;
	delete user2;
	delete database;
}*/



