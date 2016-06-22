/*
 * Server.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: juanma
 */

#include "Server.h"
#include "Resources/Logger.h"

Server::Server() {
	//this->s_http_port = "8000";
	this->manager = new Manager();
	this->eventFactory = new EventHandlerFactory();
	this->sManager = new SharedManager();
	this->running = false;
	this->lastStatisticRun = 0;
}

Server::~Server() {
	this->running = false;
	if(this->statistics.joinable()) {
		this->statistics.join(); // Wait for running thread
	}
	mg_mgr_free(&mgr);
	delete manager;
	delete eventFactory;
	delete sManager;
}


void Server::init(){
	mg_mgr_init(&mgr, this);
	nc = mg_bind(&mgr, "8000", ev_handler);
	mg_set_protocol_http_websocket(nc);
	this->running = true;
	if(!this->statistics.joinable()) {
		this->statistics = std::thread(&Server::statisticCalculations, this);
	}
}


void Server::uninit(){
	this->running = false;
	if(this->statistics.joinable()) {
		this->statistics.join(); // Wait for running thread
	}
	mg_mgr_free(&mgr);
}

void Server::update(){
	mg_mgr_poll(&mgr, 1000);
}


void Server::handleEvent(struct mg_connection* nc, int ev, void* ev_data){
		struct http_message *hm = (struct http_message *) ev_data;
		switch(ev) {
			case MG_EV_HTTP_REQUEST: {
				printf("Llego un request \n");
				LoggerManager::getInstance()->log(LoggerManager::logInfo, " Request arrived to the Server ");
				LoggerManager::getInstance()->log(LoggerManager::logDebug, "Request Body: " + std::string(hm->body.p));
				EventHandler* ehandler = eventFactory->getEventHandler(nc, hm);
				ehandler->handle(this->manager, this->sManager);
				LoggerManager::getInstance()->log(LoggerManager::logInfo, " Request processed");
				printf("Procesado un request \n");
				break;
			}
			default:
				break;
		}
}

void Server::setManager(Manager* mg){
	if(manager != NULL) {
		delete manager;
		manager = NULL;
	}
	manager = mg;
}

Manager* Server::getManager(){
	return manager;
}

void Server::setSharedManager(SharedManager* sm) {
	this->sManager = sm;
}


SharedManager* Server::getSharedManager() {
	return this->sManager;
}

bool Server::isRunning() {
	return this->running;
}


void Server::statisticCalculations() {
	time_t todayTime;
	while(this->running) {
		time (&todayTime);
		if(this->lastStatisticRun + 60 > todayTime) {
			sleep(1);
			continue;
		}
		std::cout << "Statistics running.." << std::endl;
		LoggerManager::getInstance()->log(LoggerManager::logInfo, "Statistics running..");
		this->popularCalculatorAlgorithm(this->manager);
		time (&this->lastStatisticRun);
		char lastRun[30];
		struct tm * timeinfoLast;
		timeinfoLast = localtime (&this->lastStatisticRun);
		strftime (lastRun, 30, "%c", timeinfoLast);
		std::cout << "Statistics finish at: " + std::string(lastRun) << std::endl;
		LoggerManager::getInstance()->log(LoggerManager::logInfo, "Statistics finish at: " + std::string(lastRun));
		sleep(2);
	}
}

void Server::popularCalculatorAlgorithm(Manager* manager) {
	vector<Json::Value> users = manager->getAllUsers();
	int total = users.size();
	User* actualUser = NULL;
	Json::Value userJson;
	int onePercent = total/100;
	if(!onePercent) onePercent = 1;
	LoggerManager::getInstance()->log(LoggerManager::logInfo, "Popular percent amount: " + std::to_string(onePercent));
	int i = 0;
	std::sort(users.begin(), users.end(), orderByLikesDesc);
	while(i < total) {
		userJson = users.at(i);
		actualUser = new User(userJson.get("username", "").asString());
		actualUser->initWithJson(userJson);
		if(onePercent) {
			LoggerManager::getInstance()->log(LoggerManager::logDebug, actualUser->getUsername() + " is Popular.");
			actualUser->setIsPopular();
			onePercent--;
		} else {
			actualUser->setIsNotPopular();
		}
		manager->updateUser(actualUser);
		delete actualUser;
		actualUser = NULL;
		i++;
	}
}

bool orderByLikesDesc(Json::Value u1, Json::Value u2) {
	return (u1.get("likesReceived", 0).asInt() > u2.get("likesReceived", 0).asInt());
}