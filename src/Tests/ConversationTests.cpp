#include <gtest/gtest.h>

#include "../User.h"
#include "../Message.h"
#include "../Conversation.h"


TEST(ConversationTests,TestNewConversation){
	User* user1 = new User("Juan");
	User* user2 = new User("Carlos");
	Conversation* conv = new Conversation(user1,user2, "0");
	conv->setId("0");
	ASSERT_EQ("0", conv->getId());
	ASSERT_EQ(0, conv->getNumberMessages());
	ASSERT_EQ(user1, conv->getUser1());
	ASSERT_EQ(user2, conv->getUser2());
	conv->setUser1(user1);
	ASSERT_EQ(user1, conv->getUser1());
	conv->setUser2(user2);
	ASSERT_EQ(user2, conv->getUser2());
	conv->addOneMessage();
	ASSERT_EQ(1, conv->getNumberMessages());
	conv->setNumberMessages(2);
	ASSERT_EQ(2, conv->getNumberMessages());

	delete user1;
	delete user2;
	delete conv;


}