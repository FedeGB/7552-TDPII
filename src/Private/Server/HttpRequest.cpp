/*
 * HttpRequest.cpp
 *
 *  Created on: 26/03/2016
 *      Author: demian
 */

#include <Server/HttpRequest.h>
#include <mongoose/mongoose.h>

HttpRequest::HttpRequest(http_message* httpMessage) {
	this->httpMessage = httpMessage;
	this->getStructure();
}

HttpRequest::~HttpRequest() {
	// TODO Auto-generated destructor stub
}

void HttpRequest::getStructure(){
	copyString(method, httpMessage->method);
	copyString(uri, httpMessage->uri);
	copyString(body, httpMessage->body);
}

void HttpRequest::copyString(char destination[], mg_str& mgString){
	memcpy(destination, mgString.p, mgString.len);
	destination[mgString.len] = '\0';
}

char* HttpRequest::getMethod(){
	return method;
}

char* HttpRequest::getUri(){
	return uri;
}

char* HttpRequest::getBody(){
	return body;
}
