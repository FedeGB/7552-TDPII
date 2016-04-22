/*
 * Server.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: juanma
 */

#include "Server.h"
#include "Manager.h"
#include "json/json.h"

//static struct mg_serve_http_opts s_http_server_opts;

Server::Server() {
	//this->s_http_port = "8000";
	this->manager = new Manager();
	//this->mgr.user_data = this;
}

Server::~Server() {
	  mg_mgr_free(&mgr);
}


void Server::init(){
	mg_mgr_init(&mgr, this);
	nc = mg_bind(&mgr, "8000", ev_handler);
	mg_set_protocol_http_websocket(nc);
}


void Server::uninit(){
	mg_mgr_free(&mgr);
}

void Server::update(){
	mg_mgr_poll(&mgr, 1000);
}

void Server::handleLogin(struct mg_connection *nc, struct http_message *hm) {
	char user[100], password[100];

	/* Get form variables */
	mg_get_http_var(&hm->query_string, "user", user, sizeof(user));
	mg_get_http_var(&hm->query_string, "password", password, sizeof(password));
	string str(user);
	string str2(password);
	/* Send headers */
	string result = this->loginUser(user, password);
	std::cout << "RESULT: " << result << std::endl;
	Json::Value param = Json::Value();
	param["token"] = result;
	response(nc, 0, "", param);
	//mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
	/* Compute the result and send it back as a JSON object */
	//mg_printf_http_chunk(nc, "{ \"token\": %s }", "asd123");
	//mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
}

void Server::handleCreateUser(struct mg_connection *nc, struct http_message *hm) {
	std::cout << hm->body.p << std::endl; // TODO: Add to logging.
	bool userWasCreated = this->manager->createUser(hm->body.p);
	if(userWasCreated) {
		response(nc, 0, "Registered", 0);
	} else {
		response(nc, 1, "Already Registered", 0);
	}
}

void Server::handleGetUser(struct mg_connection *nc, struct http_message *hm) {
    char username[100];
    mg_get_http_var(&hm->query_string, "username", username, sizeof(username));
    User* user = this->manager->getDatabase()->getUser(username);
    response(nc, 0, user->getJsonString(),"");
}

/*
string Server::readRequestHeader(mg_connection* conn, string header){
	const char* headerPointer = mg_get_header(conn, header.c_str());
	string h = "";

	if (headerPointer){
		string h1(headerPointer);
		h = h1;
	}

	return h;
}
*/

void Server::handleEvent(struct mg_connection* nc, int ev, void* ev_data){
		struct http_message *hm = (struct http_message *) ev_data;

		switch(ev){
		case MG_EV_HTTP_REQUEST: {
			printf("Llego un request \n");

			//HttpRequest request(hm);s
			//HttpRequestHandler requestHandler;
			//requestHandler.proccesRequest(request);
			//DEVUELVE TEXTO PLANO!
			if (mg_vcmp(&hm->uri, "/users/login") == 0) {
				if(mg_vcmp(&hm->method, "GET") == 0) {
					handleLogin(nc, hm);                    /* Handle RESTful call */
				} else {
					respondNotAllowedMethod(nc);
				}
			}

			if (mg_vcmp(&hm->uri, "/users/get") == 0) {
				if(mg_vcmp(&hm->method, "GET") == 0) {
					handleGetUser(nc, hm);                    /* Handle RESTful call */
				} else {
					respondNotAllowedMethod(nc);
				}
			}

			if (mg_vcmp(&hm->uri, "/conversations/get") == 0) {
				if(mg_vcmp(&hm->method, "GET") == 0) {
					handleLogin(nc, hm);                    /* Handle RESTful call */
				} else {
					respondNotAllowedMethod(nc);
				}
			}

			if (mg_vcmp(&hm->uri, "/users/create") == 0) {
				if(mg_vcmp(&hm->method, "POST") == 0) {
					handleCreateUser(nc, hm);                /* Handle RESTful call */
				} else {
					respondNotAllowedMethod(nc);	
				}
			}
			
			respondNotFound(nc);
			printf("Procesado un request \n");

			break;
			}
		default:
			break;
		}
}

string Server::loginUser(string user, string password){
	User* userFound = this->manager->getDatabase()->getUser(user);
	std::cout << "LOGIN: " << userFound->getUsername() << std::endl;
	Json::Value jsonValue = Json::Value();
	if (password.compare(userFound->getPassword()) == 0){
		userFound->loginNow();
		jsonValue["result"] = "OK";
		jsonValue["data"] = userFound->getJson();
		return userFound->getToken();  // TODO fixear esto
	}
	return "Sucess";
}


void Server::createUser(Json::Value json){

}

void Server::setManager(Manager* mg){
	manager = mg;
}

Manager* Server::getManager(){
	return manager;
}


void Server::respondNotAllowedMethod(struct mg_connection* nc) {
	mg_printf(nc, "HTTP/1.1 405 %s\r\n", "Method Not Allowed");		
}

void Server::respondNotFound(struct mg_connection* nc) {
	mg_printf(nc, "HTTP/1.1 404 %s\r\n", "Not Found");			
}

void Server::response(struct mg_connection* nc, int errorNum, string message, Json::Value payload) {
	/* Compute the result and send it back as a JSON object */
	Json::Value json = Json::Value();
	json["errorNum"] = errorNum;
	json["message"] = message;
	if(!payload) {
		json["payload"] = Json::Value(Json::arrayValue);
	} else {
		json["payload"] = payload;
	}
	Json::FastWriter fastWriter;
	mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
	mg_printf_http_chunk(nc, fastWriter.write(json).c_str());
	mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */	
}

