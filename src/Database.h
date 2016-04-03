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
#include <string>

#include "Message.h"


using namespace rocksdb;
using namespace std;


class Database {
public:
	Database();
	virtual ~Database();

	string get(string key, string value);
	string getFromTable(ColumnFamilyHandle* tableHandler, string key);
	bool put(string key, string value);
	User* getUser(string key);
	bool saveUser(User* user);
	Message* getMessage(string emisor, string receptor, string messageID);
	bool saveMessage(Message* message);
	bool putInTable(ColumnFamilyHandle* tableHandler, string key, string value);
	Json::Value stringToJsonValue(string str);
	string JsonValueToSting(Json::Value  json);


private:
	DB* database;
	ColumnFamilyHandle* usersTable;
	ColumnFamilyHandle* conversationsTable;
	ColumnFamilyHandle* messagesTable;

};

#endif /* DATABASE_H_ */
