/*
 * Database.h
 *
 *  Created on: Mar 26, 2016
 *      Author: juanma
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
#include "json/json.h"
#include "Message.h"
#include "User.h"
#include "Conversation.h"

#include <iostream>


using namespace rocksdb;
using namespace std;


class Database {
public:
	Database();
	virtual ~Database();

	string get(string key, string value);
	string getFromColumn(ColumnFamilyHandle* tableHandler, string key);
	bool put(string key, string value);
	User* getUser(string key);
	bool saveUser(User* user);
	Message* getMessage(string emisor, string receptor, string messageID);
	std::vector<Message*> getMessages(string emisor, string receptor);
	bool saveMessage(Message* message);
	bool putInColumn(ColumnFamilyHandle* tableHandler, string key, string value);
	Json::Value stringToJsonValue(string str);
	string JsonValueToSting(Json::Value  json);
	Conversation* getConversation(string emisor, string receptor);
	bool saveConversation(string emisor, string receptor, int numberOfMessages);


private:
	DB* database;

	ColumnFamilyHandle* columnDefault;
	ColumnFamilyHandle* columnUsers;
	ColumnFamilyHandle* columnConversations;
	ColumnFamilyHandle* columnMessages;


};

#endif /* DATABASE_H_ */
