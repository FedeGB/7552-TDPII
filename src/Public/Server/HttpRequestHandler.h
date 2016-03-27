/*
 * HttpRequestHandler.h
 *
 *  Created on: 26/03/2016
 *      Author: demian
 */

#ifndef HTTPREQUESTHANDLER_H_
#define HTTPREQUESTHANDLER_H_

class HttpRequest;

class HttpRequestHandler {
public:
	HttpRequestHandler();
	virtual ~HttpRequestHandler();

	void proccesRequest(HttpRequest& httpRequest);

};

#endif /* HTTPREQUESTHANDLER_H_ */
