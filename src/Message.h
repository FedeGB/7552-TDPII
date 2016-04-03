/*
 * Message.h
 *
 *  Created on: Mar 26, 2016
 *      Author: juanma
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "User.h"
#include <iostream>

using namespace std;
//using namespace Json;


class Message {
public:
	Message(User* sender, User* receptor, string data );
	Message(Json::Value value );
	virtual ~Message();
	string getJsonString();
	Json::Value getJson();
	void initWithJson(Json::Value value);
	const string& getData() const;
	void setData(const string& data);
	const string& getDate() const;
	void setDate(const string& date);
	const string& getId() const;
	void setId(const string& id);
	User* getReceptor();
	void setReceptor(User* receptor);
	User* getSender();
	void setSender(User* sender);

private:
	User* sender;
	User* receptor;
	string id;
	string date;
	string data;

};

#endif /* MESSAGE_H_ */
