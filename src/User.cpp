/*
 * User.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: juanma
 */

#include "User.h"


User::User(string username) {
	this->username = username;
	this->latitude = 0;
	this->longitude = 0;
	this->token = "";
	this->password = "";
	//this->lastTimeConnected = NULL;
	this->name = "";
	this->id = 0;
	this->email = username;
	this->distance = 10.0;
}



User::~User() {
	// TODO Auto-generated destructor stub
}

double User::getLatitude() {
	return latitude;
}

void User::setLatitude(double latitud) {
	this->latitude = latitud;
}

double User::getLongitude() {
	return longitude;
}

void User::setLongitude(double locationY) {
	this->longitude = locationY;
}

void User::setPassword(string password) {
	this->password = password;
}
string User::getPassword() {
	return this->password;
}

// string User::getPerfilImage() {
// 	return perfilImage;
// }

// void User::setPerfilImage(string perfilImage) {
// 	this->perfilImage = perfilImage;
// }

string User::getToken() {
	return token;
}

void User::setToken(string token) {
	this->token = token;
}

string User::getUsername() {
	return username;
}

void User::setUsername(string username) {
	this->username = username;
}

void User::setId(int sharedId) {
	this->id = sharedId;
}

int User::getId() {
	return this->id;
}

string User::getJsonString() {
	Json::StreamWriterBuilder builder;
	builder.settings_["identation"] = "\t";
	return Json::writeString(builder,this->getJson());
}

Json::Value User::getJson(bool withMatches) {
	if(withMatches) return this->getJson();
	Json::Value previous = this->getJson();
	previous.removeMember("matches");
	return previous;
}

Json::Value User::getJson() {
	Json::Value value(Json::objectValue);
	//value["alias"] = this->name;
	value["id"] = this->id;
	value["username"] = this->username;
	value["name"] = this->name;
	value["password"] = this->password;
	value["email"] = this->email;
	Json::Value location = Json::Value();
    location["longitude"] = this->longitude;
    location["latitude"] = this->latitude;
	value["location"] = location;
	value["token"] = this->token;
	value["distance"] = this->distance;

	// value["photoProfile"] = this->perfilImage;

	Json::Value vec(Json::arrayValue);
	for (int i = 0 ; i < this->matches.size() ; i++){
		vec.append(this->matches.at(i));
	}
	value["matches"] = vec;

	return value;
}

void User::initWithJson(Json::Value value){
	this->id = value.get("id","").asInt();
	this->username = value.get("username","").asString();
	this->password = value.get("password","").asString();
	this->name = value.get("name","").asString();
	this->token = value.get("token","").asString();
	this->latitude = atof((value.get("location", Json::Value()).get("latitude","").asString()).c_str());
	this->longitude = atof((value.get("location", Json::Value()).get("longitude","").asString()).c_str());
	// this->perfilImage = value.get("photoProfile","").asString();
	this->email = value.get("email", "").asString();
	this->distance = value.get("distance", 10.0).asDouble();
	Json::Value vec = value.get("matches","");
	for(Json::ValueConstIterator it = vec.begin(); it != vec.end(); ++it){
		Json::Value actual = *it;
		this->matches.push_back(actual.asString());
	}
}

void User::updateWithJson(Json::Value value){
	if(value.isMember("id"))
		this->id = std::stoi(value.get("id","").asString());
	if(value.isMember("password"))
		this->password = value.get("password","").asString();
	if(value.isMember("name"))
		this->name = value.get("name","").asString();
	if(value.isMember("token"))
		this->token = value.get("token","").asString();
	if(value.isMember("location")){
		if(value.get("location","").isMember("latitude")){
			this->latitude = value.get("location","").get("latitude","").asDouble();
		}
		if(value.get("location","").isMember("longitude")){
			this->longitude = value.get("location","").get("longitude","").asDouble();
		}

	}
	// if(value.isMember("photoProfile"))
	// 	this->perfilImage = value.get("perfilImage","").asString();

	if(value.isMember("email"))
		this->email = value.get("email","").asString();
	if(value.isMember("username"))
		this->username = value.get("username","").asString();
	if(value.isMember("distance")) {
		this->distance = value.get("distance", 10.0).asDouble();
	}
}

void User::loginNow(){
	this->lastTimeConnected = time(0);
}

void User::setName(string name){
	this->name = name;
}

string User::getName(){
	return this->name;
}

vector<string> User::getMatches(){
	return this->matches;
}

void User::setMatches(vector<string> vector){
	this->matches = vector;
}

void User::addMatch(string user){
	this->matches.push_back(user);
}

void User::setEmail(string email) {
	this->email = email;
}

string User::getEmail() {
	return this->email;
}

void User::setDistance(double dis) {
	this->distance = dis;
}

double User::getDistance() {
	return this->distance;
}