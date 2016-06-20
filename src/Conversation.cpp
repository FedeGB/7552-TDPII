/*
 * Conversation.cpp
 *
 *  Created on: Mar 27, 2016
 *      Author: juanma
 */

#include "Conversation.h"

/*
Conversation::Conversation(User* user1, User* user2) {
	this->user1 = user1;
	this->user2 = user2;
	this->numberMessages = 0;
	this->id = "";

}*/

Conversation::Conversation(User* user1, User* user2) {
	this->user1 = user1;
	this->user2 = user2;
	this->numberMessages = 0;
	this->id = 0;

}

Conversation::Conversation(Json::Value value) {
	this->user1 = new User(value.get("user1","").asString());
	this->user2 = new User(value.get("user2","").asString());
	this->numberMessages = value.get("numberMessages","").asInt();
	this->id = value.get("id","").asInt();
	Json::Value vec = value.get("messagesId", Json::Value(arrayValue));
	Json::ValueConstIterator messageIt = vec.begin();
	int i = 0;
	while(messageIt != vec.end()) {
		this->messagesId.push_back((*messageIt).get(i, 0).asInt());
		messageIt++;
	}
}


Conversation::~Conversation() {
	// TODO Auto-generated destructor stub
}

int Conversation::getId() {
	return id;
}

void Conversation::setId(int id) {
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

void Conversation::addOneMessage(int msgId){
	messagesId.push_back(msgId);
	this->numberMessages++;
}

string Conversation::getJsonString() {
	Json::StreamWriterBuilder builder;
	builder.settings_["identation"] = "\t";
	return Json::writeString(builder,this->getJson());
}

Json::Value Conversation::getJson() {
	Json::Value value(Json::objectValue);
	value["user1"] = this->user1->getUsername();
	value["user2"] = this->user2->getUsername();
	value["id"] = this->id;
	value["numberMessages"] = this->numberMessages;
	Json::Value vec(Json::arrayValue);
	for (int i = 0 ; i < this->messagesId.size() ; i++){
		vec.append(this->messagesId.at(i));
	}
	value["messagesId"] = vec;
	return value;
}

const std::vector<int>& Conversation::getMessagesIds() {
	return this->messagesId;
}

