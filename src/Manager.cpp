/*
 * Manager.cpp
 *
 *  Created on: Mar 31, 2016
 *      Author: juanma
 */

#include "Manager.h"
#include "Database.h"
#include "Factories/UserFactory.h"
#include "Factories/MessageFactory.h"
#include "Factories/LikeFactory.h"


Manager::Manager() {
	this->db = new Database();
}

Manager::~Manager() {
	delete db;
}


Database* Manager::getDatabase(){
	return db;
}

void Manager::setDatabase(Database* database){
	this->db = database;
}

bool Manager::createUser(string json){
	UserFactory userFact;
	User* user = userFact.createWithJsonString(json);
	if(!user) {
		return false;
	}
	return this->db->saveUser(user);
}

bool Manager::saveMessage(string json){
	MessageFactory messageFactory;
	Message* message = messageFactory.createWithJsonString(json);
	User* sender = message->getSender();
	User* receptor = message->getReceptor();
	Conversation* conv = this->db->getConversation(sender ->getUsername(), receptor->getUsername() );
//	if(!conv){
//		conv = new Conversation(message->getSender(), message->getReceptor());
//	}
	int messageID = conv->getNumberMessages();
	message->setId(to_string(messageID));
	conv->addOneMessage();
	this->db->saveConversation(conv);
	// TODO logear
	return this->db->saveMessage(message);
}


bool Manager::saveLike(string json){
	LikeFactory likeFactory;
	Like* like = likeFactory.createWithJsonString(json);
	// TODO logear
	return 	this->db->saveLike(like);
	;
}



User* Manager::getUser(std::string user) {
	return this->db->getUser(user);	
}

Conversation* Manager::getConversation(std::string user1, std::string user2) {
	return this->db->getConversation(user1, user2);
}

vector<Message*> Manager::getMessages(string user1, string user2){
	return this->db->getMessages(user1, user2);
}


