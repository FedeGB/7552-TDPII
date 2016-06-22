/*
 * Database.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: juanma
 */

#include "Database.h"
#include "Resources/Logger.h"
#include "User.h"
#include <string>
#include <vector>

std::string kDBPath = "/tmp/rocksdb1";
std::string buDBPath = "rocksdb_backup1";

Database::Database() {

	// open DB
	Options options;
	options.create_if_missing = true;
	Status s = DB::Open(options, kDBPath, &this->database);
	// this->recoverBackUpDB();
	if(s.ok()){
		s = database->CreateColumnFamily(ColumnFamilyOptions(), "columnUsers", &this->columnUsers);
		assert(s.ok());
		s = database->CreateColumnFamily(ColumnFamilyOptions(), "columnConversations", &this->columnConversations);
		assert(s.ok());
		s = database->CreateColumnFamily(ColumnFamilyOptions(), "columnMessages", &this->columnMessages);
		assert(s.ok());
		s = database->CreateColumnFamily(ColumnFamilyOptions(), "columnLikes", &this->columnLikes);
		assert(s.ok());
		// close DB
		delete this->columnUsers;
		delete this->columnConversations;
		delete this->columnMessages;
		delete this->columnLikes;
		delete this->database;
	}/* else {
		LoggerManager::getInstance()->log(LoggerManager::logError, " Database Error ");
		return;
	}*/
	// open DB with 4 column families
	std::vector<ColumnFamilyDescriptor> column_families;
	// have to open default column family
	column_families.push_back(ColumnFamilyDescriptor(kDefaultColumnFamilyName,ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("columnUsers",ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("columnConversations",ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("columnMessages",ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("columnLikes",ColumnFamilyOptions()));

	std::vector<ColumnFamilyHandle*> handles;

	s = DB::Open(options, kDBPath ,column_families,&handles,&this->database);
	// this->recoverBackUpDB();
	if(!s.ok()) {
		LoggerManager::getInstance()->log(LoggerManager::logError, " Database Error ");
		return;
	}

	this->columnDefault = handles[0];
	this->columnUsers = handles[1];
	this->columnConversations = handles[2];
	this->columnMessages = handles[3];
	this->columnLikes = handles[4];

	LoggerManager::getInstance()->log(LoggerManager::logInfo, " Database Opened ");

	std::vector<Iterator*> iterators;
	Status status = database->NewIterators(rocksdb::ReadOptions(), handles, &iterators);
	// shows all the values of the database
	for(int i = 0 ; i < iterators.size() ; i++){
		rocksdb::Iterator* it =  iterators.at(i);
		for (it->SeekToFirst(); it->Valid(); it->Next()) {
			// cout << it->key().ToString() << ": " << it->value().ToString() << endl;
		}
		assert(it->status().ok()); // Check for any errors found during the scan
		delete it;
	}

}

Database::~Database() {
	// this->backUpDB();
	Status s;
	delete this->columnDefault;
	//s = database->DropColumnFamily(columnUsers);
	//  assert(s.ok());
	delete this->columnUsers;
	//s = database->DropColumnFamily(columnMessages);
	//  assert(s.ok());
	delete this->columnMessages;
	//s = database->DropColumnFamily(columnConversations);
	//  assert(s.ok());
	delete this->columnConversations;
	//s = database->DropColumnFamily(columnLikes);
	//assert(s.ok());
	delete this->columnLikes;
	delete this->database; // TODO agregar las columns
}

void Database::backUpDB() {
	BackupEngine* backup_engine;
	Status s;
	s = BackupEngine::Open(Env::Default(), BackupableDBOptions(buDBPath), &backup_engine);
	if(!s.ok()) {
		delete backup_engine;
		return;
	}
	s = backup_engine->CreateNewBackup(this->database);
	if(!s.ok()) {
		delete backup_engine;
		return;
	}
	std::vector<BackupInfo> backup_info;
	backup_engine->GetBackupInfo(&backup_info);
	// you can get IDs from backup_info if there are more than two
	// s = backup_engine->VerifyBackup(1 /* ID */);
	// assert(s.ok());
	// s = backup_engine->VerifyBackup(2 /* ID */);
	// assert(s.ok());
	delete backup_engine;
}

void Database::recoverBackUpDB() {
	BackupEngineReadOnly* backup_engine;
	Status s = BackupEngineReadOnly::Open(Env::Default(), BackupableDBOptions(buDBPath), &backup_engine);
	if(!s.ok()) {
		delete backup_engine;
		return;
	}
	backup_engine->RestoreDBFromLatestBackup(kDBPath, kDBPath);
	delete backup_engine;
}

bool Database::put(string key, string value){
	Status  s = database->Put(WriteOptions(), key, value);
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
	if(userload) {
		return false;
	}
	return this->putInColumn(this->columnUsers,username,json);
}

bool Database::updateUser(User* user){
	string username = user->getUsername();
	string json = user->getJsonString();
	return this->putInColumn(this->columnUsers,username,json);
}


User* Database::getUser(string username) {
	string json = this->getFromColumn(this->columnUsers, username);
	if(json.empty()) return NULL;
	Json::Value jsonValue = this->stringToJsonValue(json);
	User* user = new User(username);
	user->initWithJson(jsonValue);
	return user;
}


vector<Json::Value> Database::getUsers(){
	vector<Json::Value> users;
	rocksdb::Iterator* it = this->database->NewIterator(rocksdb::ReadOptions(), this->columnUsers);
	for (it->SeekToFirst(); it->Valid(); it->Next()) {
			string key = it->key().ToString();
			User* userActual = this->getUser(key);
			Json::Value val =  userActual->getJson();
			users.push_back(val);
			//cout << it->key().ToString() << ": " << it->value().ToString() << endl;
	}
	assert(it->status().ok()); // Check for any errors found during the scan
	delete it;
	return users;
}

Like* Database::getLike(string searchString) {
	string json = this->getFromColumn(this->columnLikes, searchString);
	if(json.empty()) {
		return NULL;
	}
	Json::Value jsonValue = this->stringToJsonValue(json);
	Like* like = new Like(jsonValue);
	return like;
}

bool Database::saveMessage(Message* message) {
	string json = message->getJsonString();
	string aux = message->getId();
	aux += message->getSender()->getUsername();
	aux += message->getReceptor()->getUsername();
	return this->putInColumn(this->columnMessages,aux,json);
}

Message* Database::getMessage(string emisor, string receptor, string messageID){
	Message* message;
	string aux = messageID+emisor+receptor;
	string json = this->getFromColumn(this->columnMessages, aux);
	if(json == ""){
		aux = messageID+receptor+emisor;
		json = this->getFromColumn(this->columnMessages, aux);
	}
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
		string aux = to_string(intId)+emisor+receptor;
		message = this->getMessage(emisor, receptor, to_string(intId));
		//if(message)
		intId++;
		messages.push_back(message);
	}
	return messages;
}

vector<Json::Value> Database::getAllMessages(){
	vector<Json::Value> messages;
	rocksdb::Iterator* it = this->database->NewIterator(rocksdb::ReadOptions(), this->columnMessages);
	for (it->SeekToFirst(); it->Valid(); it->Next()) {
		string key = it->key().ToString();
		Json::Value actualMessage = Json::Value(stringToJsonValue(it->value().ToString()));
		messages.push_back(actualMessage);
	}
	assert(it->status().ok()); // Check for any errors found during the scan
	delete it;
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
			//User* user1 = this->getUser(emisor);
			//User* user2 = this->getUser(receptor);
			return new Conversation(new User(emisor), new User(receptor));
		}
	}
	Json::Value jsonValue = this->stringToJsonValue(json);
	Conversation* conv = new Conversation(jsonValue);
	return conv;
}




bool Database::saveLike(Like* like){
	string user1 = like->getUser1()->getUsername();
	string user2 = like->getUser2()->getUsername();
	string aux = user1 + user2;
	string json = like->getJsonString();
	LoggerManager::getInstance()->log(LoggerManager::logDebug, 
	"Guardando like de " + user1 + " a " + user2 );
	return this->putInColumn(columnLikes, aux, json);
}

bool Database::saveConversation(Conversation* conversation){
	string user1 = conversation->getUser1()->getUsername();
	string user2 = conversation->getUser2()->getUsername();
	string aux = user1 + user2;
	string json = conversation->getJsonString();
	//Conversation* conv = this->getConversation(user1, user2);
	//if (!conv){
	//	return false;
	//}
	return this->putInColumn(columnConversations, aux, json);
}

Json::Value Database::stringToJsonValue(string str) {
	Json::Reader r = Json::Reader();
	Json::Value val = Json::Value();
	r.parse(str,val,false);
	return val;
}

bool Database::deleteUser(User *user) {
	Status s = database->Delete(rocksdb::WriteOptions(), this->columnUsers, user->getUsername());
	return s.ok();
}

bool Database::deleteConversation(Conversation* conv) {
	string user1 = conv->getUser1()->getUsername();
	string user2 = conv->getUser2()->getUsername();
	std::vector<int> msgIds = conv->getMessagesIds();
	Message* msg = NULL;
	for (std::vector<int>::iterator it = msgIds.begin() ; it != msgIds.end(); ++it) {
		msg = this->getMessage(user1, user2, std::to_string(*it));
		this->deleteMessage(msg);
		delete msg;
		msg = NULL;
	}
	string aux = user1 + user2;
	Status s = database->Delete(rocksdb::WriteOptions(), this->columnConversations, aux);
	return s.ok();
}

bool Database::deleteMessage(Message* msg) {
	string json = msg->getJsonString();
	string aux = msg->getId();
	aux += msg->getSender()->getUsername();
	aux += msg->getReceptor()->getUsername();
	Status s = database->Delete(rocksdb::WriteOptions(), this->columnMessages, aux);
	return s.ok();
}

bool Database::deleteLike(Like* like) {
	string user1 = like->getUser1()->getUsername();
	string user2 = like->getUser2()->getUsername();
	string aux = user1 + user2;
	Status s = database->Delete(rocksdb::WriteOptions(), this->columnLikes, aux);
	return s.ok();
}
