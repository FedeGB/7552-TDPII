/*
 * User.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: juanma
 */

#include "User.h"
#import "Utils.h"

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
	this->minAge = 18;
	this->maxAge = 25;
	this->lastCandiatesRequest = 0;
	this->likesReceived = 0;
	this->popularOnePercent = false;
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

bool User::requestWasToday() {
	char lastDate[10];
	char todayDate[10];
	struct tm * timeinfoLast;
	struct tm * timeinfoToday;
	time_t todayTime;
	time (&todayTime);

	timeinfoLast = localtime (&this->lastCandiatesRequest);
	strftime (lastDate, 10, "%D", timeinfoLast);

	timeinfoToday = localtime (&todayTime);
	strftime (todayDate, 10, "%D", timeinfoToday);
	if(strcmp(lastDate, todayDate) == 0) {
		return true;
	}
	return false;
}

void User::updateLastRequest() {
	time (&this->lastCandiatesRequest);
}

void User::updateCandidatesSend(int amount) {
	this->candidatesSend += amount;
}

void User::resetCandidatesSend() {
	this->candidatesSend = 0;
}

bool User::hasReachedMaxCandidatesSend() {
	return (this->candidatesSend >= 20);
}


void User::oneLikeUp() {
	this->likesReceived++;
}

int User::getLikesReceived() {
	return this->likesReceived;
}

bool User::returnAsCandidate() {
	if(this->popularOnePercent) {
		srand (time(NULL));
		int random = rand() % 2; // 50 / 50
		LoggerManager::getInstance()->log(LoggerManager::logDebug, this->username + ". Random: " + std::to_string(random));
		if(random == 0) {
			return true;
		} else {
			return false;
		}
	}
	return true;
}

void User::setIsPopular() {
	this->popularOnePercent = true;
}

void User::setIsNotPopular() {
	this->popularOnePercent = false;
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
	Json::Value range = Json::Value();
	range["min"] = this->minAge;
	range["max"] = this->maxAge;
	value["ageRange"] = range;
	value["lastCandiatesRequest"] = (int)this->lastCandiatesRequest;
	value["candidatesSend"] = this->candidatesSend;
	value["popularOnePercent"] = this->popularOnePercent;
	value["likesReceived"] = this->likesReceived;
	// value["photoProfile"] = this->perfilImage;

	Json::Value vec(Json::arrayValue);
	for (int i = 0 ; i < this->matches.size() ; i++){
		vec.append(this->matches.at(i));
	}
	value["matches"] = vec;

	return value;
}

void User::initWithJson(Json::Value value){
	if(value.get("id", 0).isInt()) {
		this->id = value.get("id", 0).asInt();	
	} else {
		this->id = std::stoi(value.get("id", "0").asString());
	}
	this->username = value.get("username","").asString();

	string passwordGiven = value.get("password","").asString();
	char *hashedPass = new char[passwordGiven.length() + 1];
	strcpy(hashedPass, passwordGiven.c_str());
	string hashedPassResult = SHA256(hashedPass);
	delete [] hashedPass;

	this->password =  hashedPassResult;
	this->name = value.get("name","").asString();
	this->token = value.get("token","").asString();
	this->latitude = value.get("location", Json::Value()).get("latitude", 0.0).asDouble();
	this->longitude = value.get("location", Json::Value()).get("longitude", 0.0).asDouble();
	// this->perfilImage = value.get("photoProfile","").asString();
	this->email = value.get("email", "").asString();
	this->distance = value.get("distance", 10.0).asDouble();
	this->minAge = value.get("ageRange", Json::Value()).get("min", 18).asInt();
	this->maxAge = value.get("ageRange", Json::Value()).get("max", 25).asInt();
	Json::Value vec = value.get("matches","");
	for(Json::ValueConstIterator it = vec.begin(); it != vec.end(); ++it){
		Json::Value actual = *it;
		this->matches.push_back(actual.asString());
	}
	this->candidatesSend = value.get("candidatesSend", 0).asInt();
	this->lastCandiatesRequest = (time_t)value.get("lastCandiatesRequest", 0).asInt();
	this->popularOnePercent = value.get("popularOnePercent", false).asBool();
	this->likesReceived = value.get("likesReceived", 0).asInt();
}

void User::updateWithJson(Json::Value value){
	if(value.isMember("id"))
		this->id = std::stoi(value.get("id","").asString());
	if(value.isMember("password")){

		string passwordGiven = value.get("password","").asString();

		char *hashedPass = new char[passwordGiven.length() + 1];
		strcpy(hashedPass, passwordGiven.c_str());
		string hashedPassResult = SHA256(hashedPass);
		delete [] hashedPass;
		this->password =hashedPassResult;

	}
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
	if(value.isMember("ageRange")) {
		this->minAge = value.get("ageRange", Json::Value()).get("min", 18).asInt();
		this->maxAge = value.get("ageRange", Json::Value()).get("max", 25).asInt();
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

int User::getMaxAge() {
	return this->maxAge;
}

void User::setMaxAge(int max) {
	this->maxAge = max;
}

int User::getMinAge() {
	return this->minAge;
}

void User::setMinAge(int min) {
	this->minAge = min;
}