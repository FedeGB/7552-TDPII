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
#include "Match.h"
#include "Like.h"
#include <iostream>


using namespace rocksdb;
using namespace std;


class Database {
public:
	Database();
	virtual ~Database();

	bool put(string key, string value);
	bool putInColumn(ColumnFamilyHandle* tableHandler, string key, string value);

	string get(string key, string value);
	string getFromColumn(ColumnFamilyHandle* tableHandler, string key);

//gets
	User* getUser(string key);
	Message* getMessage(string emisor, string receptor, string messageID);
	std::vector<Message*> getMessages(string emisor, string receptor);
	Conversation* getConversation(string emisor, string receptor);
	Match* getMatch(string user1, string user2);

// saves
	bool saveUser(User* user);
	bool saveMessage(Message* message);
	bool saveConversation(Conversation* conversation);
	bool saveLike(Like* like);
	bool saveMatch(Match* match);

	Json::Value stringToJsonValue(string str);
	string JsonValueToSting(Json::Value  json);

private:

	DB* database;
	ColumnFamilyHandle* columnDefault;
	ColumnFamilyHandle* columnUsers;
	ColumnFamilyHandle* columnConversations;
	ColumnFamilyHandle* columnMessages;
	ColumnFamilyHandle* columnLikes;



};

#endif /* DATABASE_H_ */
