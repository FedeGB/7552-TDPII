/*
 * User.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: juanma
 */

#include "User.h"


User::User(string name) {
	this->username = name;
	this->locationX = 0;
	this->locationY = 0;
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

double User::getLocationX() const {
	return locationX;
}

void User::setLocationX(double locationX) {
	this->locationX = locationX;
}

double User::getLocationY() const {
	return locationY;
}

void User::setLocationY(double locationY) {
	this->locationY = locationY;
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

Json::Value User::getJson() {
	Json::Value value(Json::objectValue);
	value["username"] = this->username;
	value["password"] = this->password;
	value["name"] = this->name;
	value["token"] = this->token;
	value["locationX"] = this->locationX;
	value["locationY"] = this->locationY;
	value["perfilImage"] = this->perfilImage;
	return value;
}

void User::initWithJson(Json::Value value){
	this->username = value.get("username","").asString();
	std::cout << this->username << std::endl;
	this->password = value.get("password","").asString();
	std::cout << this->password << std::endl;

	this->name = value.get("name","").asString();
	std::cout << this->name << std::endl;

	this->token = value.get("token","").asString();
	this->locationX = atof((value.get("locationX","").asString()).c_str());
	this->locationY = atof((value.get("locationY","").asString()).c_str());
	this->perfilImage = value.get("perfilImage","").asString();
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


