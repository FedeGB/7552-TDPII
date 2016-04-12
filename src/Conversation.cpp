/*
 * Conversation.cpp
 *
 *  Created on: Mar 27, 2016
 *      Author: juanma
 */

#include "Conversation.h"
#include "User.h"


Conversation::Conversation(User* user1, User* user2) {
	this->user1 = user1;
	this->user2 = user2;
	this->numberMessages = 0;
	this->id = "";

}

Conversation::Conversation(Json::Value value) {
	this->user1 = new User(value.get("user1","").asString());
	this->user1 = new User(value.get("user2","").asString());
	this->numberMessages = value.get("numberMessages","").asInt();
	this->id = value.get("id","").asString();
}


Conversation::~Conversation() {
	// TODO Auto-generated destructor stub
}

const string& Conversation::getId() const {
	return id;
}

void Conversation::setId(const string& id) {
	this->id = id;
}

int Conversation::getNumberMessages() const {
	return numberMessages;
}

void Conversation::setNumberMessages(int numberMessages) {
	this->numberMessages = numberMessages;
}

User* Conversation::getUser1() {
	return user1;
}

void Conversation::setUser1(User* user1) {
	this->user1 = user1;
}

User* Conversation::getUser2()  {
	return user2;
}

void Conversation::setUser2( User* user2) {
	this->user2 = user2;
}

void Conversation::addOneMessage(){
	this->numberMessages++;
}


