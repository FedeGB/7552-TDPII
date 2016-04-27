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
	if(mg_vcmp(&hm->method, this->methodType.c_str()) != 0) {
		this->respondNotAllowedMethod();
		return false;
	}
	return true;
}

void EventHandler::respondNotAllowedMethod() {
	mg_printf(nc, "HTTP/1.1 405 %s\r\nTransfer-Encoding: chunked\r\n\r\n", "Method Not Allowed");
	mg_printf_http_chunk(nc, "");
	mg_send_http_chunk(nc, "", 0);
}

void EventHandler::respondNotFound() {
	mg_printf(nc, "HTTP/1.1 404 %s\r\nTransfer-Encoding: chunked\r\n\r\n", "Not Found");
	mg_printf_http_chunk(nc, "");
	mg_send_http_chunk(nc, "", 0);
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
	Json::Value metadata = Json::Value();
	metadata["size"] = (int)json["payload"].size();
	json["metadata"] = metadata;
	Json::FastWriter fastWriter;
	mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\nContent-Type: application/json\r\n\r\n");
	mg_printf_http_chunk(nc, fastWriter.write(json).c_str());
	mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */	
}
