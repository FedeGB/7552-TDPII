/*
 * Database.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: juanma
 */

#include "Database.h"
#include "User.h"
#include <string>


std::string kDBPath = "/tmp/rocksdb2";

Database::Database() {

	// open DB
	Options options;
	options.create_if_missing = true;
	Status s = DB::Open(options, kDBPath, &this->database);
	if(s.ok()){
		s = database->CreateColumnFamily(ColumnFamilyOptions(), "columnUsers", &this->columnUsers);
		assert(s.ok());
		s = database->CreateColumnFamily(ColumnFamilyOptions(), "columnConversations", &this->columnConversations);
		assert(s.ok());
		s = database->CreateColumnFamily(ColumnFamilyOptions(), "columnMessages", &this->columnMessages);
		assert(s.ok());
		// close DB
		delete this->columnUsers;
		delete this->columnConversations;
		delete this->columnMessages;
		delete this->database;
	}
	// open DB with 4 column families
	std::vector<ColumnFamilyDescriptor> column_families;
	// have to open default column family
	column_families.push_back(ColumnFamilyDescriptor(kDefaultColumnFamilyName,ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("columnUsers",ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("columnConversations",ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("columnMessages",ColumnFamilyOptions()));
	std::vector<ColumnFamilyHandle*> handles;

	s = DB::Open(options, kDBPath ,column_families,&handles,&this->database);
	assert(s.ok());

	this->columnDefault = handles[0];
	this->columnUsers = handles[1];
	this->columnConversations = handles[2];
	this->columnMessages = handles[3];

}

Database::~Database() {

	Status s;
	delete this->columnDefault;
	s = database->DropColumnFamily(columnUsers);
	  assert(s.ok());
	delete this->columnUsers;
	s = database->DropColumnFamily(columnMessages);
	  assert(s.ok());
	delete this->columnMessages;
	s = database->DropColumnFamily(columnConversations);
	  assert(s.ok());
	delete this->columnConversations;
	delete this->database; // TODO agregar las columns


}

bool Database::put(string key, string value){
	Status  s = database->Put(WriteOptions(), key, value);
	//bool s = this->putInColumn(this->columnDefault, key, value);
	return s.ok();

}

string Database::get(string key, string value){
	Status s = database->Get(ReadOptions(), key, &value); // TODO fixear esto, que reciba puntero o no reciba value
	return value;
}

bool Database::putInColumn(ColumnFamilyHandle* tableHandler, string key, string value){
	Status s = database->Put(WriteOptions(), tableHandler, key, value);
	return s.ok();
}

string Database::getFromColumn(ColumnFamilyHandle* tableHandler, string key){
	string value;
	Status s = database->Get(ReadOptions(), tableHandler, key, &value);
	return value;
}

bool Database::saveUser(User* user) {
	string username = user->getUsername();
	string json = user->getJsonString();
	User* userload = this->getUser(username);
	if(!userload->getUsername().empty()) {
		return false;
	}
	return this->putInColumn(this->columnUsers,username,json);
}
User* Database::getUser(string username) {
	string json = this->getFromColumn(this->columnUsers, username);
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
	return this->putInColumn(this->columnMessages,aux,json);
	return true;
}

Message* Database::getMessage(string emisor, string receptor, string messageID){
	Message* message;
	//Conversation* conv = this->getConversation(emisor, receptor);
	string aux = messageID;
	aux+=emisor;
	aux+=receptor;
	//if (conv->getNumberMessages() == 0){
	//	return NULL;
	//}
	//else{
		string json = this->getFromColumn(this->columnMessages, aux);
		Json::Value jsonValue = this->stringToJsonValue(json);
		//message->initWithJson(jsonValue);
		message = new Message(jsonValue);
	//}
	return message;
}

std::vector<Message*> Database::getMessages(string emisor, string receptor){
	Message* message;
	Conversation* conv = this->getConversation(emisor, receptor);
	int intId = conv->getId();
	string id = to_string(intId);
	int numberOfMessages = conv->getNumberMessages();
	std::vector<Message*> messages;
	for ( int i = 0; i < numberOfMessages; i++){
		std::stringstream result;
		result << numberOfMessages;
		string aux = result.str()+emisor+receptor;
		message = this->getMessage(emisor, receptor, aux);
		messages.push_back(message);
	}
	return messages;
}


Conversation* Database::getConversation(string emisor, string receptor){
	string aux = emisor;
	aux+=receptor;
	string json = this->getFromColumn(this->columnConversations, aux);
	if(json == ""){
		aux=receptor+emisor;
		json = this->getFromColumn(this->columnConversations, aux);
		if(json == ""){
			User* user1 = this->getUser(emisor);
			User* user2 = this->getUser(receptor);
			return new Conversation(user1, user2);
		}
	}
	Json::Value jsonValue = this->stringToJsonValue(json);
	Conversation* conv = new Conversation(jsonValue);
	return conv;
}


Match* Database::getMatch(string user1, string user){
	//TODO terminar esto
}

bool Database::saveMatch(Match* match){
	//TODO terminar esto

}


bool Database::saveConversation(Conversation* conversation){
	string user1 = conversation->getUser1()->getUsername();
	string user2 = conversation->getUser2()->getUsername();
	string aux = user1 + user2;
	string json = conversation->getJsonString();
	Conversation* conv = this->getConversation(user1, user2);
	if (!conv){
		return false;
	}
	return this->putInColumn(columnConversations, aux, json);
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




