/*
 * Manager.cpp
 *
 *  Created on: Mar 31, 2016
 *      Author: juanma
 */

#include "Manager.h"

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
	User* user = new User(json);
	this->db->saveUser(user);
	return "pl";
}
