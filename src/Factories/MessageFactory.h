/*
 * MessageFactory.h
 *
 *  Created on: Mar 31, 2016
 *      Author: juanma
 */

#ifndef MESSAGEFACTORY_H_
#define MESSAGEFACTORY_H_

#include "Factory.h"

class MessageFactory: public Factory {
public:
	MessageFactory();
	virtual ~MessageFactory();
};

#endif /* MESSAGEFACTORY_H_ */
