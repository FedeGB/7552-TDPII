/*
 * ApplicationServerConnection.cpp
 *
 *  Created on: 21/03/2016
 *      Author: demian
 */

#include <Server/ApplicationServerConnection.h>
#include <Server/HttpRequest.h>
#include <Server/HttpRequestHandler.h>

ApplicationServerConnection::ApplicationServerConnection() {
	this->nc = NULL;
	serverConnection = this;
}

ApplicationServerConnection::~ApplicationServerConnection() {
	// TODO Auto-generated destructor stub
}

void ApplicationServerConnection::update(RestServer& restServer){
	mg_mgr_poll(&mgr, 1000);
}

void ApplicationServerConnection::init(){
	mg_mgr_init(&mgr, NULL);
	nc = mg_bind(&mgr, "1234", ev_handler);
	mg_set_protocol_http_websocket(nc);
}

void ApplicationServerConnection::uninit(){
	mg_mgr_free(&mgr);
}

void ApplicationServerConnection::handleEvent(struct mg_connection* nc, int ev, void* ev_data){
		struct http_message *hm = (struct http_message *) ev_data;

		switch(ev){
		case MG_EV_HTTP_REQUEST: {
			HttpRequest request(hm);
			HttpRequestHandler requestHandler;
			requestHandler.proccesRequest(request);
			//DEVUELVE TEXTO PLANO!
			mg_printf(nc, "HTTP/1.1 200 OK\r\n"
	                "Content-Type: text/plain\r\n"
	                "Content-Length: 21\r\n\r\n"
			"{ User : \"Username\" }");
			break;
			}
		default:
			break;
		}
}

