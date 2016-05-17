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
}

//User::User(Json::Value value){
//	this->initWithJson(value);
//}

User::~User() {
	// TODO Auto-generated destructor stub
}

double User::getLatitude() const {
	return latitude;
}

void User::setLatitude(double latitud) {
	this->latitude = latitud;
}

double User::getLongitude() const {
	return longitude;
}

void User::setLongitude(double locationY) {
	this->longitude = locationY;
}

void User::setPassword(const string& password) {
	this->password = password;
}
string User::getPassword() {
	return this->password;
}

const string& User::getPerfilImage() const {
	return perfilImage;
}

void User::setPerfilImage(const string& perfilImage) {
	this->perfilImage = perfilImage;
}

const string& User::getToken() const {
	return token;
}

void User::setToken(const string& token) {
	this->token = token;
}

const string& User::getUsername() const {
	return username;
}

void User::setUsername(const string& username) {
	this->username = username;
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
	value["alias"] = this->username;
	value["name"] = this->name;
	value["password"] = this->password;
	value["email"] = this->email;
	Json::Value location = Json::Value();
    location["longitude"] = this->longitude;
    location["latitude"] = this->latitude;
	value["location"] = location;
	value["photoProfile"] = this->perfilImage;

	Json::Value vec(Json::arrayValue);
	for (int i = 0 ; i < this->matches.size() ; i++){
		vec.append(this->matches.at(i));
	}
	value["matches"] = vec;

	return value;
}

void User::initWithJson(Json::Value value){
	this->username = value.get("alias","").asString();
	this->password = value.get("password","").asString();
	this->name = value.get("name","").asString();
	this->token = value.get("token","").asString();
	this->latitude = atof((value.get("latitud","").asString()).c_str());
	this->longitude = atof((value.get("longitude","").asString()).c_str());
	this->perfilImage = value.get("perfilImage","").asString();
	this->email = value.get("email", "").asString();
	Json::Value vec = value.get("matches","");
	for(Json::ValueConstIterator it = vec.begin(); it != vec.end(); ++it){
		Json::Value actual = *it;
		this->matches.push_back(actual.asString());
	}
}

void User::loginNow(){
	this->lastTimeConnected = time(0);
}

void User::setName(const string& name){
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

const string& User::getEmail() {
	return this->email;
}