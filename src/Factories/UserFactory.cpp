/*
 * UserFactory.cpp
 *
 *  Created on: Mar 31, 2016
 *      Author: juanma
 */

#include "UserFactory.h"

UserFactory::UserFactory() {
	// TODO Auto-generated constructor stub

}

UserFactory::~UserFactory() {
	// TODO Auto-generated destructor stub
}



User* UserFactory::createUser(string username, string password){
	User* u = new User(username);
	u->setPassword(password);
	return u;
}

User* UserFactory::createWithJsonValue(Json::Value value) {
	string name = value.get("name", "").asString();
	string username = value.get("username","").asString();
	string password = value.get("password", "").asString();
	double locationX = value.get("locationX", 0).asDouble();
	double locationY =  value.get("locationY", 0).asDouble();
	string perfilImage = value.get("perfilImage", "").asString();
	//time_t lastTimeConnected = value.get("lastTimeConnected", "").asDouble();
	string token = value.get("token","").asString();

	User* u = new User(username);
	u->setPassword(password);
	u->setName(name);
	u->setToken(token);
	u->setPerfilImage(perfilImage);
	u->setLocationX(locationX);
	u->setLocationY(locationY);
	return u;
}


User* UserFactory::createWithJsonString(string json) {
	Json::Reader r = Json::Reader();
	Json::Value val = Json::Value();
	r.parse(json,val,false);
	return this->createWithJsonValue(val);
}
