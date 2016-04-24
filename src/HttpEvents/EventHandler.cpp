#include "EventHandler.h"

EventHandler::EventHandler(struct mg_connection *nco, struct http_message *hme) {
	this->nc = nco;
	this->hm = hme;
}

EventHandler::EventHandler() {

}

EventHandler::~EventHandler() {

}

void EventHandler::handle(Manager* manager) {

}

bool EventHandler::validateInput() {

}

void EventHandler::respondNotAllowedMethod() {
	mg_printf(nc, "HTTP/1.1 405 %s\r\n", "Method Not Allowed");		
}

void EventHandler::respondNotFound() {
	mg_printf(nc, "HTTP/1.1 404 %s\r\n", "Not Found");			
}

void EventHandler::response(int errorNum, std::string message, Json::Value payload) {
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
