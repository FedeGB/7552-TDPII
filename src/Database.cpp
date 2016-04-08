/*
 * Database.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: juanma
 */

#include "Database.h"
#include "User.h"

std::string DBpath = "/tmp/match";

Database::Database() {
	Options options;
	  // create the DB if it's not already present
	options.create_if_missing = true;
	  // open DB
	Status s = DB::Open(options, DBpath, &database);
	 // std::cout << s.ToString() << std::endl;
/*	if(s.ok()){
		s = database->CreateColumnFamily(ColumnFamilyOptions(), "UsersTable", &this->usersTable);
		assert(s.ok());
		s = database->CreateColumnFamily(ColumnFamilyOptions(), "messagesTable", &this->messagesTable);
		assert(s.ok());
		s = database->CreateColumnFamily(ColumnFamilyOptions(), "conversationsTable", &this->conversationsTable);
		assert(s.ok());
	  }*/
	// TODO construir las columnas
	  assert(s.ok());
}

Database::~Database() {
	delete this->database;
	delete this->usersTable;
	delete this->messagesTable;
	delete this->conversationsTable;
}

bool Database::put(string key, string value){
	Status s = database->Put(WriteOptions(), key, value);
	return s.ok();
}

string Database::get(string key, string value){
	Status s = database->Get(ReadOptions(), key, &value); // TODO fixear esto, que reciba puntero o no reciba value
	return value;
}

bool Database::putInTable(ColumnFamilyHandle* tableHandler, string key, string value){
	Status s = database->Put(WriteOptions(), tableHandler, key, value);
	return s.ok();
}

string Database::getFromTable(ColumnFamilyHandle* tableHandler, string key){
	string value;
	Status s = database->Get(ReadOptions(), key, &value);
	return value;
}

bool Database::saveUser(User* user) {
	string username = user->getUsername();
	string json = user->getJsonString();
	return this->putInTable(this->usersTable,username,json);
	return true;
}
User* Database::getUser(string username) {
	string json = this->getFromTable(this->usersTable, username);
	Json::Value jsonValue = this->stringToJsonValue(json);
	User* user = new User(username);
	user->initWithJson(jsonValue);
	return user;
}

bool Database::saveMessage(Message* message) {
	string json = message->getJsonString();
	string aux = message->getId();
	aux += message->getSender()->getUsername();
	aux += message->getReceptor()->getUsername();
	return this->putInTable(this->messagesTable,aux,json);
	return true;
}

Message* Database::getMessage(string emisor, string receptor, string messageID){
	string aux = messageID;
	aux+=emisor;
	aux+=receptor;
	string json = this->getFromTable(this->messagesTable, aux);
	Json::Value jsonValue = this->stringToJsonValue(json);
	Message* message = new Message(jsonValue);
	message->initWithJson(jsonValue);
	return message;
}

Json::Value Database::stringToJsonValue(string str) {
	Json::Reader r = Json::Reader();
	Json::Value val = Json::Value();
	r.parse(str,val,false);
	return val;
}

string JsonValueToSting(Json::Value  json){
	Json::StreamWriterBuilder builder;
	builder.settings_["identation"] = "\t";
	return Json::writeString(builder,json);
}




