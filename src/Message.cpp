/*
 * Message.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: juanma
 */

#include "Message.h"
#include "User.h"

Message::Message(User* sender, User* receptor, string data ) {
	// TODO Auto-generated constructor stub
	this->sender = sender;
	this->receptor = receptor;
	this->data = data;
	this->id = "";
}

Message::Message(Json::Value value ) {
	// TODO Auto-generated constructor stub
	User* senderUser = new User(value.get("sender","").asString());
	this->sender = senderUser;
	User* receptorUser = new User(value.get("receptor","").asString());
	this->receptor = receptorUser;
	this->id = value.get("id","").asString();
	this->data = value.get("data","").asString();
	this->date = value.get("date","").asString();

}

Message::~Message() {
	// TODO Auto-generated destructor stub
}


string Message::getJsonString() {
	Json::StreamWriterBuilder builder;
	builder.settings_["identation"] = "\t";
	return Json::writeString(builder,this->getJson());
}

Json::Value Message::getJson() {
	Json::Value value(Json::objectValue);
	value["sender"] = this->sender;
	value["receptor"] = this->receptor;
	value["id"] = this->id;
	value["data"] = this->data;
	value["date"] = this->date;
	return value;
}

void Message::initWithJson(Json::Value value){
	//this->sender = value.get("sender","").asString();
	//this->receptor = value.get("receptor","").asString();
	//this->id = value.get("id","").asString();
	//this->data = value.get("data","").asString();
	//this->date = value.get("date","").asDouble();
}

const string& Message::getData() const {
	return data;
}

void Message::setData(const string& data) {
	this->data = data;
}

const string& Message::getDate() const {
	return date;
}

void Message::setDate(const string& date) {
	this->date = date;
}

const string& Message::getId() const {
	return id;
}

void Message::setId(const string& id) {
	this->id = id;
}

User* Message::getReceptor() {
	return receptor;
}

void Message::setReceptor(User* receptor) {
	this->receptor = receptor;
}

User* Message::getSender() {
	return sender;
}

void Message::setSender( User* sender) {
	this->sender = sender;
}
