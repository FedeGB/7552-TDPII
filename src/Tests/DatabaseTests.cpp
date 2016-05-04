#include <gtest/gtest.h>
#include "../User.h"
#include "../Message.h"
#include "../Database.h"
#include "../Like.h"


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
	user->setLatitude(20.0);
	user->setLongitude(40.0);
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
	user->setLatitude(20.0);
	user->setLongitude(40.0);
	user->setPerfilImage("URL");
	database->saveUser(user);
	ASSERT_EQ(user->getName(), database->getUser(user->getUsername())->getName());
	delete user;
	delete database;
}


TEST(DatabaseTests,TestSaveAndGetConversation){
	Database* database = new Database();
	User* user1 = new User("User1");
	User* user2 = new User("User2");
	database->saveUser(user1);
	database->saveUser(user2);
	Conversation* conversation = new Conversation(user1, user2);
	ASSERT_EQ(conversation->getJsonString(), database->getConversation(user1->getUsername(), user2->getUsername())->getJsonString());
	delete user1;
	delete user2;
	delete conversation;
	delete database;
}


TEST(DatabaseTests,TestSaveAndGetLike) {
	Database* database = new Database();
	User* user1 = new User("User1");
	User* user2 = new User("User2");
	database->saveUser(user1);
	database->saveUser(user2);
	Like* like = new Like(user1, user2, true);
	database->saveLike(like);
	ASSERT_EQ(like->getJsonString(), database->getLike(user1->getUsername()+user2->getUsername())->getJsonString());
	delete user1;
	delete user2;
	delete like;
	delete database;
}


TEST(DatabaseTests,TestSaveAndGetMessage){
	Database* database = new Database();
	User* user1 = new User("User1");
	User* user2 = new User("User2");
	string data = "hola";
	Conversation* conv = database->getConversation(user1->getUsername(), user2->getUsername());
	int id;
	if(conv){
		conv->getId();
	}else{
		id = 0;
	}
	Message* message = new Message(user1, user2, data);
	message->setId(to_string(id));
	database->saveMessage(message);
	ASSERT_EQ(data, database->getMessage(user1->getUsername(), user2->getUsername(), to_string(id))->getData());
	delete user1;
	delete user2;
	delete database;
	delete conv;
	delete message;
}

TEST(DatabaseTests,TestSaveTwoMessages){
	Database* database = new Database();
	User* user1 = new User("User1");
	User* user2 = new User("User2");
	string data = "Hi";
	string dataTwo = "How are you? ";
	Conversation* conv = database->getConversation(user1->getUsername(), user2->getUsername());
	Message* message = new Message(user1, user2, data);
	message->setId("0");
	database->saveMessage(message);
	Message* messageTwo = new Message(user2, user1, dataTwo);
	messageTwo->setId("1");
	database->saveMessage(messageTwo);

	vector<Message*> messages = database->getMessages(user1->getUsername(), user2->getUsername());
	vector<Message*> originalMessages;
	originalMessages.push_back(message);
	originalMessages.push_back(messageTwo);
//	for ( int i = 0 ; i < messages.size(); i++){
//		ASSERT_EQ(data, database->getMessage(user1->getUsername(), user2->getUsername(), "0")->getData());
//	}
	ASSERT_EQ(data, database->getMessage(user1->getUsername(), user2->getUsername(), "0")->getData());
	ASSERT_EQ(dataTwo, database->getMessage(user2->getUsername(), user1->getUsername(), "1")->getData());
	delete user1;
	delete user2;
	delete database;
	delete conv;
	delete message;
}







