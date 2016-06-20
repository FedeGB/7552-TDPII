#include <gtest/gtest.h>
#include "../User.h"
#include "../Message.h"
#include "../Database.h"
#include "../Manager.h"

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
	int previous = database->getUsers().size();
	User* user = new User("User1" + std::to_string(previous));
	user->setPassword("hola");
	user->setName("Juan");
	user->setLatitude(20.0);
	user->setLongitude(40.0);
	// user->setPerfilImage("URL");
	database->saveUser(user);
	ASSERT_EQ(user->getName(), database->getUser(user->getUsername())->getName());
	database->deleteUser(user);
	delete user;
	delete database;
}


TEST(DatabaseTests,TestSaveAndGetUser){
	Database* database = new Database();
	int previous = database->getUsers().size();
	User* user = new User("User1" + std::to_string(previous));
	user->setPassword("hola");
	user->setName("Juan");
	user->setLatitude(20.0);
	user->setLongitude(40.0);
	// user->setPerfilImage("URL");
	database->saveUser(user);
	ASSERT_EQ(user->getName(), database->getUser(user->getUsername())->getName());
	database->deleteUser(user);
	delete user;
	delete database;
}


TEST(DatabaseTests,TestSaveAndGetAllUsers){
	Database* database = new Database();
	int previous = database->getUsers().size();
	User* user = new User("User1" + std::to_string(previous));
	user->setPassword("hola");
	user->setName("Juan");
	user->setLatitude(20.0);
	user->setLongitude(40.0);
	// user->setPerfilImage("URL");
	database->saveUser(user);
	User* user2 = new User("User2" + std::to_string(previous + 1));
	database->saveUser(user2);
	ASSERT_EQ(previous + 2, database->getUsers().size());
	database->deleteUser(user);
	database->deleteUser(user2);
	delete user;
	delete user2;
	delete database;
}


TEST(DatabaseTests,TestSaveAndGetConversation){
	Database* database = new Database();
	int previous = database->getUsers().size();
	User* user1 = new User("User1" + std::to_string(previous));
	User* user2 = new User("User2" + std::to_string(previous + 1));
	database->saveUser(user1);
	database->saveUser(user2);
	Conversation* conversation = new Conversation(user1, user2);
	ASSERT_EQ(conversation->getJsonString(), database->getConversation(user1->getUsername(), user2->getUsername())->getJsonString());
	database->deleteUser(user1);
	database->deleteUser(user2);
	database->deleteConversation(conversation);
	delete user1;
	delete user2;
	delete conversation;
	delete database;
}


TEST(DatabaseTests,TestSaveAndGetLike) {
	Database* database = new Database();
	int previous = database->getUsers().size();
	User* user1 = new User("User1" + std::to_string(previous));
	User* user2 = new User("User2" + std::to_string(previous + 1));
	database->saveUser(user1);
	database->saveUser(user2);
	Like* like = new Like(user1, user2, true);
	database->saveLike(like);
	ASSERT_EQ(like->getJsonString(), database->getLike(user1->getUsername()+user2->getUsername())->getJsonString());
	//delete user1;
	//delete user2;
	database->deleteLike(like);
	database->deleteUser(user1);
	database->deleteUser(user2);
	delete like;
	delete database;
}


TEST(DatabaseTests,TestSaveAndGetMessage){
	Database* database = new Database();
	int previous = database->getUsers().size();
	User* user1 = new User("User1" + std::to_string(previous));
	User* user2 = new User("User2" + std::to_string(previous + 1));
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
	ASSERT_EQ(data, database->getMessage(user2->getUsername(), user1->getUsername(), to_string(id))->getData());
	database->deleteUser(user1);
	database->deleteUser(user2);
	delete user1;
	delete user2;
	delete conv;
	delete message;
	delete database;
}

TEST(DatabaseTests,TestUpdateUser){
	Database* database = new Database();
	int previous = database->getUsers().size();
	User* user = new User("User1" + std::to_string(previous));
	user->setPassword("hola");
	user->setName("Juan");
	user->setLatitude(20.0);
	user->setLongitude(40.0);
	// user->setPerfilImage("URL");
	database->saveUser(user);
	// std::cout << database->getUser(user->getUsername())->getPerfilImage() << std::endl;
	ASSERT_EQ(user->getName(), database->getUser(user->getUsername())->getName());
	// ASSERT_EQ("URL", database->getUser(user->getUsername())->getPerfilImage());
	// user->setPerfilImage("URL2");
	database->updateUser(user);
	// ASSERT_EQ("URL2", database->getUser(user->getUsername())->getPerfilImage());
	database->deleteUser(user);
	delete user;
	delete database;
}

TEST(DatabaseTests,TestSaveTwoMessages){
	Database* database = new Database();
	int previous = database->getUsers().size();
	User* user1 = new User("User1" + std::to_string(previous));
	User* user2 = new User("User2" + std::to_string(previous + 1));
	string data = "Hi";
	string dataTwo = "How are you? ";
	Conversation* conv = database->getConversation(user1->getUsername(), user2->getUsername());
	database->saveConversation(conv);
	previous = database->getAllMessages().size();
	Message* message = new Message(user1, user2, data);
	message->setId("0");
	database->saveMessage(message);
	Message* messageTwo = new Message(user2, user1, dataTwo);
	messageTwo->setId("1");
	database->saveMessage(messageTwo);
	conv->addOneMessage(0);
	conv->addOneMessage(1);


	vector<Message*> messages = database->getMessages(user1->getUsername(), user2->getUsername());
	vector<Message*> originalMessages;
	originalMessages.push_back(message);
	originalMessages.push_back(messageTwo);
//	for ( int i = 0 ; i < messages.size(); i++){
//		ASSERT_EQ(data, database->getMessage(user1->getUsername(), user2->getUsername(), "0")->getData());
//	}
	ASSERT_EQ(data, database->getMessage(user1->getUsername(), user2->getUsername(), "0")->getData());
	ASSERT_EQ(dataTwo, database->getMessage(user2->getUsername(), user1->getUsername(), "1")->getData());
	ASSERT_EQ(previous + 1, database->getAllMessages().size());
	database->deleteUser(user1);
	database->deleteUser(user2);
	database->deleteConversation(conv);
	delete user1;
	delete user2;
	delete database;
	delete conv;
	delete message;
}
