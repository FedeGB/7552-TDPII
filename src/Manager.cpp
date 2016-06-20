/*
 * Manager.cpp
 *
 *  Created on: Mar 31, 2016
 *      Author: juanma
 */

#include "Manager.h"
#include "Resources/Logger.h"


Manager::Manager() {
	this->db = new Database();
}

Manager::~Manager() {
	delete db;
}


Database* Manager::getDatabase(){
	return db;
}

void Manager::setDatabase(Database* database){
	this->db = database;
}

bool Manager::createUser(string json){
	UserFactory userFact;
	User* user = userFact.createWithJsonString(json);
	if(!user) {
		return false;
	}
	return this->db->saveUser(user);
}

bool Manager::deleteUser(string username){
	User* userToDelete = this->getDatabase()->getUser(username);
	if(!userToDelete) return false;
	return this->db->deleteUser(userToDelete);
}

bool Manager::updateUser(User* user) {
	return this->getDatabase()->updateUser(user);
}

bool Manager::saveMessage(string json){
	MessageFactory messageFactory;
	Message* message = messageFactory.createWithJsonString(json);
	User* sender = message->getSender();
	User* receptor = message->getReceptor();
	Conversation* conv = this->db->getConversation(sender ->getUsername(), receptor->getUsername() );

	int messageID = conv->getNumberMessages();
	message->setId(to_string(messageID));
	conv->addOneMessage();
	this->db->saveConversation(conv);
	LoggerManager::getInstance()->log(LoggerManager::logInfo, "New Message created");
	return this->db->saveMessage(message);
}


bool Manager::saveLike(string json){
	LikeFactory likeFactory;
	LoggerManager::getInstance()->log(LoggerManager::logInfo, "Incoming json:" + json );
	Like* like = likeFactory.createWithJsonString(json);
	LoggerManager::getInstance()->log(LoggerManager::logDebug, "Like created" );
	User* userLiked = like->getUser2();
	userLiked = this->getUser(userLiked->getUsername());
	userLiked->oneLikeUp();
	this->updateUser(userLiked);
	if(thereIsMatch(like)){
		LoggerManager::getInstance()->log(LoggerManager::logInfo,
		"Hubo match entre " + like->getUser1()->getUsername() + " y " + like->getUser2()->getUsername() );
		User* user1 = like->getUser1();
		User* user2 = like->getUser2();
		user1->addMatch(user2->getUsername());
		user2->addMatch(user1->getUsername());
	}
	return 	this->db->saveLike(like);
}

bool Manager::thereIsMatch(Like* like){
	Like* theOtherLike = this->getLike(like->getUser2()->getUsername()+like->getUser1()->getUsername());
	if(theOtherLike && theOtherLike->getLike()){
		User* user1 = this->db->getUser(like->getUser1()->getUsername());
		User* user2 = this->db->getUser(like->getUser2()->getUsername());
		user1->addMatch(user2->getUsername());
		user2->addMatch(user1->getUsername());
		this->db->updateUser(user1);
		this->db->updateUser(user2);
		return true;
	}
	return false;
}

bool Manager::thereIsMatch(string json){
	LikeFactory likeFactory;
	Like* like = likeFactory.createWithJsonString(json);
	Like* theOtherLike = this->getLike(like->getUser2()->getUsername()+like->getUser1()->getUsername());
	return theOtherLike && theOtherLike->getLike();
}

User* Manager::getUser(std::string user) {
	return this->db->getUser(user);
}

Like* Manager::getLike(string searchString) {
	return this->db->getLike(searchString);
}


Conversation* Manager::getConversation(std::string user1, std::string user2) {
	return this->db->getConversation(user1, user2);
}

vector<Message*> Manager::getMessages(string user1, string user2){
	return this->db->getMessages(user1, user2);
}

vector<string> Manager::getMatches(string user){
	return this->db->getUser(user)->getMatches();
}

vector<Json::Value> Manager::getAllUsers(){
	return this->db->getUsers();
}

vector<Json::Value> Manager::getAllMessages(){
	return this->db->getAllMessages();
}

