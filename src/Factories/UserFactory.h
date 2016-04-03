/*
 * UserFactory.h
 *
 *  Created on: Mar 31, 2016
 *      Author: juanma
 */

#ifndef USERFACTORY_H_
#define USERFACTORY_H_

#include "Factory.h"
#include <string>
#include "../User.h"

using namespace std;

class UserFactory: public Factory {
public:
	UserFactory();
	virtual ~UserFactory();
	User* createUser(string json);

};

#endif /* USERFACTORY_H_ */
