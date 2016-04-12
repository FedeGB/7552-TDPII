/*
 * Database.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: juanma
 */

#include "Database.h"
#include "User.h"
#include <string>


std::string kDBPath = "/tmp/rocksdb";

Database::Database() {


/*

	printf("ENTRA ACA1 \n");

	DB* db;
	  Options options;
	  // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
	  // create the DB if it's not already present
	  options.create_if_missing = true;

	  // open DB
	  Status s = DB::Open(options, kDBPath, &db);
		printf("ENTRA ACA2 \n");

	  assert(s.ok());
		printf("ENTRA ACA3 \n");

	  // Put key-value
	  s = db->Put(WriteOptions(), "key1", "value");
	  assert(s.ok());
	  std::string value;
	  // get value
	  s = db->Get(ReadOptions(), "key1", &value);
	  assert(s.ok());
	  assert(value == "value");

	  // atomically apply a set of updates
	  {
	    WriteBatch batch;
	    batch.Delete("key1");
	    batch.Put("key2", value);
	    s = db->Write(WriteOptions(), &batch);
	  }

	  s = db->Get(ReadOptions(), "key1", &value);
	  assert(s.IsNotFound());

	  db->Get(ReadOptions(), "key2", &value);
	  assert(value == "value");


*/

	printf("ENTRA AL INIT \n");

	// open DB
	Options options;
	options.create_if_missing = true;
	Status s = DB::Open(options, kDBPath, &this->database);
	assert(s.ok());
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
	// open DB with 4 column families
	std::vector<ColumnFamilyDescriptor> column_families;
	// have to open default column family
	column_families.push_back(ColumnFamilyDescriptor(kDefaultColumnFamilyName,ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("columnUsers",ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("columnConversations",ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("columnMessages",ColumnFamilyOptions()));
	std::vector<ColumnFamilyHandle*> handles;
	printf("DESP DEL HANDLE \n");

	Status status = DB::Open(options, kDBPath ,column_families,&handles,&this->database);
	assert(s.ok());
	printf("DESP DEL SEGUNDO OPEN \n");

	this->columnDefault = handles[0];
	this->columnUsers = handles[1];
	this->columnConversations = handles[2];
	this->columnMessages = handles[3];
	printf("SALE DEL INIT \n");



}

Database::~Database() {
/*
	delete this->columnDefault;
	delete this->columnUsers;
	delete this->columnMessages;
	delete this->columnConversations;
	delete this->database; // TODO agregar las columns

*/


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
	printf("ENTRA ACA 2\n");
	Status  s = database->Put(WriteOptions(), key, value);

	//bool s = this->putInColumn(this->columnDefault, key, value);
	return s.ok();
	printf("ENTRA ACA 3\n");

}

string Database::get(string key, string value){
	Status s = database->Get(ReadOptions(), key, &value); // TODO fixear esto, que reciba puntero o no reciba value
	return value;
}

bool Database::putInColumn(ColumnFamilyHandle* tableHandler, string key, string value){
	Status s = database->Put(WriteOptions(), tableHandler, key, value);
	printf("ENTRA ACA \n");
	return s.ok();
}

string Database::getFromColumn(ColumnFamilyHandle* tableHandler, string key){
	string value;
	Status s = database->Get(ReadOptions(), tableHandler, key, &value);
	return value;
}

bool Database::saveUser(User* user) {
	printf("ENTRA ACA 3\n");

	string username = user->getUsername();
	string json = user->getJsonString();
	printf("ENTRA ACA4 \n");

	return this->putInColumn(this->columnUsers,username,json);
	printf("ENTRA ACA 5\n");

	return true;
}
User* Database::getUser(string username) {
	string json = this->getFromColumn(this->columnUsers, username);
	std::cout << "MUESTRO EL JSON" << std::endl;

	std::cout << json << std::endl;

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
	Conversation* conv = this->getConversation(emisor, receptor);
	string aux = messageID;
	aux+=emisor;
	aux+=receptor;
	if (conv->getNumberMessages() == 0){
		return NULL;
	}
	else{
		string json = this->getFromColumn(this->columnMessages, aux);
		Json::Value jsonValue = this->stringToJsonValue(json);
		message->initWithJson(jsonValue);
		message = new Message(jsonValue);
	}
	return message;
}

std::vector<Message*> Database::getMessages(string emisor, string receptor){
	Message* message;
	Conversation* conv = this->getConversation(emisor, receptor);
	string id = conv->getId();
	int numberOfMessages = conv->getNumberMessages();
	std::vector<Message*> messages;
	string convId = conv->getId();
	for ( int i = 0; i < numberOfMessages; i++){
		std::stringstream result;
		result << numberOfMessages;
		string aux = result.str()+emisor+receptor;
		message = this->getMessage(emisor, receptor, aux);
		messages.push_back(message);
	}
//
//	if (conv->getNumberMessages() == 0){
//		return messages;
//	}
//	else{
//		string json = this->getFromColumn(this->columnMessages, aux);
//		Json::Value jsonValue = this->stringToJsonValue(json);
//		message->initWithJson(jsonValue);
//		message = new Message(jsonValue);
//	}
	return messages;
}


Conversation* Database::getConversation(string emisor, string receptor){
	string aux = emisor;
	aux+=receptor;
	string json = this->getFromColumn(this->columnConversations, aux);
	if(json == ""){
		aux=receptor+emisor;
		json = this->getFromColumn(this->columnConversations, aux);
		if(json == "") return NULL;
	}
	Json::Value jsonValue = this->stringToJsonValue(json);
	Conversation* conv = new Conversation(jsonValue);
	return conv;
}


bool saveConversation(string emisor, string receptor, int numberOfMessages){

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




