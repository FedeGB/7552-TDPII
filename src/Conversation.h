/*
 * Conversation.h
 *
 *  Created on: Mar 27, 2016
 *      Author: juanma
 */

#ifndef CONVERSATION_H_
#define CONVERSATION_H_

#include <string>
#include "json/json.h"
#include "User.h"
#include "Message.h"

class User;

using namespace std;

class Conversation {
public:
	//Conversation(User* user1, User* user2);
	Conversation(User* user1, User* user2);

	Conversation(Json::Value value);
	virtual ~Conversation();
	int getId();
	void setId(int id);
	int getNumberMessages() const;
	void setNumberMessages(int numberMessages);
	User* getUser1();
	void setUser1(User* user1);
	User* getUser2();
	void setUser2(User* user2);
	void addOneMessage(int);
	const std::vector<int>& getMessagesIds();

	Json::Value getJson();
	string getJsonString();


private:
	int id;
	User* user1;
	User* user2;
	int numberMessages;
	std::vector<int> messagesId;

};

#endif /* CONVERSATION_H_ */
