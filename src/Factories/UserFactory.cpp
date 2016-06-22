/*
 * UserFactory.cpp
 *
 *  Created on: Mar 31, 2016
 *      Author: juanma
 */

#include "UserFactory.h"
#include "../Utils.h"

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

	char *hashedPass = new char[password.length() + 1];
	strcpy(hashedPass, password.c_str());
	string hashedPassResult = SHA256(hashedPass);
	delete [] hashedPass;

	double locationX, locationY;
	if(value.isMember("location")) {
		locationX = value.get("location", Json::Value()).get("latitude", 0.0).asDouble();
		locationY = value.get("location", Json::Value()).get("longitude", 0.0).asDouble();
	} else {
		locationX = value.get("latitude", 0.0).asDouble();
		locationY =  value.get("longitude", 0.0).asDouble();
	}
	// string perfilImage = value.get("perfilImage", "").asString();
	string email = value.get("email", "").asString();
	//time_t lastTimeConnected = value.get("lastTimeConnected", "").asDouble();
	string token = value.get("token","").asString();
	double distance = value.get("distance", 10.0).asDouble();
	int minAge, maxAge;
	if(!value.isMember("ageRange")) {
		minAge = value.get("edad", 18).asInt();
		maxAge = value.get("edad", 18).asInt() + 7;
	} else {
		minAge = value.get("ageRange", Json::Value()).get("min", 18).asInt();
		maxAge = value.get("ageRange", Json::Value()).get("max", 25).asInt();
	}

	User* u = new User(username);
	u->setPassword(hashedPassResult);
	u->setName(name);
	u->setToken(token);
	u->setEmail(email);
	u->setLatitude(locationX);
	u->setLongitude(locationY);
	u->setDistance(distance);
	u->setMaxAge(maxAge);
	u->setMinAge(minAge);
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
