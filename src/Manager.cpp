/*
 * Manager.cpp
 *
 *  Created on: Mar 31, 2016
 *      Author: juanma
 */

#include "Manager.h"
#include "Database.h"
#include "Factories/UserFactory.h"

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

User* Manager::getUser(std::string user) {
	return this->db->getUser(user);	
}

Conversation* Manager::getConversation(std::string user1, std::string user2) {
	return this->db->getConversation(user1, user2);
}
