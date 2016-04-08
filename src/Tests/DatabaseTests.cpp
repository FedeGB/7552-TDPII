#include <gtest/gtest.h>
#include "../User.h"
#include "../Message.h"
#include "../Database.h"





TEST(UsersTests,TestSaveKeyValue){
	Database* database = new Database();
	string key = "key";
	string value = "value";
	bool res = database->put(key,value);
	ASSERT_EQ(true, res);
	string aux;
	string expectedValue = database->get(key, aux);
	ASSERT_EQ(value,expectedValue);

//	User* user = new User("User1");
//	user->setPassword("hola");
//	user->setName("Juan");
//	user->setLocationX(20.0);
//	user->setLocationY(40.0);
//	user->setPerfilImage("URL");
//	ASSERT_EQ("User1", user->getUsername());
//	ASSERT_EQ("hola", user->getPassword());
//	ASSERT_EQ("Juan", user->getName());
//	ASSERT_EQ(20.0, user->getLocationX());
//	ASSERT_EQ(40.0, user->getLocationY());
//	ASSERT_EQ("URL", user->getPerfilImage());
//	delete user;
}


