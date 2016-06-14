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
	double locationX = value.get("latitud", 0).asDouble();
	double locationY =  value.get("longitude", 0).asDouble();
	// string perfilImage = value.get("perfilImage", "").asString();
	string email = value.get("email", "").asString();
	//time_t lastTimeConnected = value.get("lastTimeConnected", "").asDouble();
	string token = value.get("token","").asString();
	double distance = value.get("distance", 10.0).asDouble();

	User* u = new User(username);
	u->setPassword(password);
	u->setName(name);
	u->setToken(token);
	u->setEmail(email);
	// u->setPerfilImage(perfilImage);
	u->setLatitude(locationX);
	u->setLongitude(locationY);
	u->setDistance(distance);
	return u;
}


User* UserFactory::createWithJsonString(string json) {
	Json::Reader r = Json::Reader();
	Json::Value val = Json::Value();
	r.parse(json.c_str(),val);
	val["token"] = val.get("username", "").asString() + val.get("password", "").asString();
	val["email"] = val.get("username", "").asString();
	return this->createWithJsonValue(val);
}
