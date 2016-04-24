/*
 * MessageFactory.cpp
 *
 *  Created on: Mar 31, 2016
 *      Author: juanma
 */

#include "MessageFactory.h"

MessageFactory::MessageFactory() {
	// TODO Auto-generated constructor stub

}

MessageFactory::~MessageFactory() {
	// TODO Auto-generated destructor stub
}


Message* MessageFactory::createWithJsonValue(Json::Value value) {
    string user1 = value.get("user1", "").asString();
    string user2 = value.get("user2","").asString();
    string data = value.get("data", "").asString();
    User* usr1 = new User(user1);
    User* usr2 = new User(user2);
    Message* msg = new Message(usr1, usr2, data);
    return msg;
}

Message* MessageFactory::createWithJsonString(string json) {
    Json::Reader r = Json::Reader();
    Json::Value val = Json::Value();
    r.parse(json.c_str(),val);
    return this->createWithJsonValue(val);
}
