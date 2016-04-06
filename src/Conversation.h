/*
 * Conversation.h
 *
 *  Created on: Mar 27, 2016
 *      Author: juanma
 */

#ifndef CONVERSATION_H_
#define CONVERSATION_H_

#include <string>

class User;

using namespace std;

class Conversation {
public:
	Conversation();
	virtual ~Conversation();
	const string& getId() const;
	void setId(const string& id);
	int getNumberMessages() const;
	void setNumberMessages(int numberMessages);
	User* getUser1();
	void setUser1(User* user1);
	User* getUser2();
	void setUser2(User* user2);

private:
	string id;
	User* user1;
	User* user2;
	int numberMessages;
};

#endif /* CONVERSATION_H_ */
