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

string Manager::createUser(string json){
	UserFactory userFact;
	User* user = userFact.createWithJsonString(json);
	this->db->saveUser(user);
	return "pl";
}
