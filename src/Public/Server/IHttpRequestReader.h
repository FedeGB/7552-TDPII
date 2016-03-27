/*
 * IHttpRequestReader.h
 *
 *  Created on: 26/03/2016
 *      Author: demian
 */

#ifndef IHTTPREQUESTREADER_H_
#define IHTTPREQUESTREADER_H_

class IHttpRequestReader {
public:
	virtual char* getMethod() = 0;
	virtual char* getUri() = 0;
	virtual char* getBody() = 0;

	virtual ~IHttpRequestReader() {}
};

#endif /* IHTTPREQUESTREADER_H_ */
