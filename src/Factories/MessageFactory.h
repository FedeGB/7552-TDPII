/*
 * MessageFactory.h
 *
 *  Created on: Mar 31, 2016
 *      Author: juanma
 */

#ifndef MESSAGEFACTORY_H_
#define MESSAGEFACTORY_H_

#include "Factory.h"
#include "../Message.h"
#include "../User.h"

class MessageFactory: public Factory {
public:
	MessageFactory();
	virtual ~MessageFactory();
	Message* createWithJsonValue(Json::Value value);
	Message* createWithJsonString(string json);
	};

#endif /* MESSAGEFACTORY_H_ */
