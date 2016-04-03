/*
 * UserFactory.cpp
 *
 *  Created on: Mar 31, 2016
 *      Author: juanma
 */

#include "UserFactory.h"

UserFactory::UserFactory() {
	// TODO Auto-generated constructor stub

}

UserFactory::~UserFactory() {
	// TODO Auto-generated destructor stub
}

User* UserFactory::createUser(string json){
	User* user = new User(json);
}
