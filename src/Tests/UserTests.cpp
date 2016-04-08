#include <gtest/gtest.h>
#include "../User.h"
#include "../Message.h"



TEST(UsersTests,TestNewUser){
	string user1 = "User1";
	User* user = new User(user1);
	user->setPassword("hola");
	user->setName("Juan");
	user->setLocationX(20.0);
	user->setLocationY(40.0);
	user->setPerfilImage("URL");
	ASSERT_EQ("User1", user->getUsername());
	ASSERT_EQ("hola", user->getPassword());
	ASSERT_EQ("Juan", user->getName());
	ASSERT_EQ(20.0, user->getLocationX());
	ASSERT_EQ(40.0, user->getLocationY());
	ASSERT_EQ("URL", user->getPerfilImage());
	delete user;
}




TEST(UsersTests, TestJson){
/*	User* user = new User("User1");
	Json::Value value;
	value.Value("username:");
	u1->initWithJson(value);
	string body = "Testing";
	Message* m = new Message(u1,u2,body);
	ASSERT_EQ(u1->getUsername(),m->getEmisor()->getUsername());
	ASSERT_EQ(u2->getUsername(),m->getReceptor()->getUsername());
	ASSERT_EQ(body,m->getBody());

	delete u1;
	delete u2;
	delete m;*/
}
