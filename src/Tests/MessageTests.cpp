#include <gtest/gtest.h>
#include "../User.h"
#include "../Message.h"



TEST(MessageTests,TestSenderAndReceptor){
	User* user1 = new User("User1");
	User* user2 = new User("User2");
	string data = "Testing";
	Message* message = new Message(user1,user2,data);
	ASSERT_EQ(user1->getUsername(),message->getSender()->getUsername());
	ASSERT_EQ(user2->getUsername(),message->getReceptor()->getUsername());
	ASSERT_EQ(data,message->getData());
	delete user1;
	delete user2;
	delete message;
}


TEST(MessageTests,TestId){
	User* user1 = new User("User1");
	User* user2 = new User("User2");
	string data = "Testing";
	Message* message = new Message(user1,user2,data);
	message->setId("2");
	ASSERT_EQ("2",message->getId());
	delete user1;
	delete user2;
	delete message;
}


TEST(MessageTests,TestMessageJson){
	User* user1 = new User("User1");
	User* user2 = new User("User2");
	string data = "Testing";
	Message* message = new Message(user1,user2,data);
	message->setReceptor(user2);
	message->setSender(user1);
	ASSERT_EQ(user1->getUsername(),message->getSender()->getUsername());
	ASSERT_EQ(user2->getUsername(),message->getReceptor()->getUsername());
	delete user1;
	delete user2;
	delete message;
}
