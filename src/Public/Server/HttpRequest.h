/*
 * HttpRequest.h
 *
 *  Created on: 26/03/2016
 *      Author: demian
 */

#ifndef HTTPREQUEST_H_
#define HTTPREQUEST_H_

struct http_message;
struct mg_str;

#include <Server/IHttpRequestReader.h>

class HttpRequest : public IHttpRequestReader {
public:
	HttpRequest(http_message* httpMessage);
	virtual ~HttpRequest();

	char* getMethod();
	char* getUri();
	char* getBody();

private:
	http_message* httpMessage;
	void getStructure();
	void copyString(char destination[], mg_str& mgString);

	//Armo con una longitud fija maxima para evitar andar reservando
	//y borrando memoria en el loop principal cada vez que llega un httpRequest
	char method[10];
	char uri[50];
	char body[1000];
};



#endif /* HTTPREQUEST_H_ */
