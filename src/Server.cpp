/*
 * Server.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: juanma
 */

#include "Server.h"
#include "Manager.h"

static struct mg_serve_http_opts s_http_server_opts;

Server::Server() {
	this->s_http_port = "8000";
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

static void handleLogin(struct mg_connection *nc, struct http_message *hm) {
	char user[100], password[100];
	double result;

	/* Get form variables */
	mg_get_http_var(&hm->query_string, "user", user, sizeof(user));
	mg_get_http_var(&hm->query_string, "password", password, sizeof(password));
	string str(user);
	string str2(password);
	std::cout << str << str2 << std::endl;
	printf("%c \n",user);
	printf("%c \n", password);
	/* Send headers */
	mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
	/* Compute the result and send it back as a JSON object */
	//mg_printf_http_chunk(nc, "{ \"user\": %s password : %s }", str, str2);
	mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
}

void Server::handleCreateUser(struct mg_connection *nc, struct http_message *hm) {
	char user[100], password[100];
	Json::Value value;
	/* Get form variables */
	mg_get_http_var(&hm->body, "user", user, sizeof(user));
	mg_get_http_var(&hm->body, "password", password, sizeof(password));
	printf("This is the body : %s \n", hm->body.p);
	string str(user);
	string str2(password);
	std::cout << str << str2 << std::endl;
	printf("%c \n",user);
	printf("%c \n", password);
	printf("pasa \n");
	this->manager->createUser(hm->body.p);
	/* Send headers */
	mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
	/* Compute the result and send it back as a JSON object */
	//mg_printf_http_chunk(nc, "{ \"user\": %s password : %s }", str, str2);
	mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
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
			if (mg_vcmp(&hm->uri, "/api/login") == 0) {
				handleLogin(nc, hm);                    /* Handle RESTful call */
			}
			if (mg_vcmp(&hm->uri, "/api/createUser") == 0) {
				handleCreateUser(nc, hm);                /* Handle RESTful call */
			}
			mg_printf(nc, "HTTP/1.1 200 OK\r\n"
	                "Content-Type: text/plain\r\n"
	                "Content-Length: 21\r\n\r\n"
			"{ User : \"Username\" }");
			printf("Procesado un request \n");

			break;
			}
		default:
			break;
		}
}

string Server::login(string user, string password){
	User* userFound = this->manager->getDatabase()->getUser(user);
	Json::Value jsonValue = Json::Value();
	if (password.compare(userFound->getPassword()) == 0){
		userFound->loginNow();
		jsonValue["result"] = "OK";
		jsonValue["data"] = userFound->getJson();
	}
}


void Server::createUser(Json::Value json){

}

void Server::setManager(Manager* mg){
	manager = mg;
}

Manager* Server::getManager(){
	return manager;
}


