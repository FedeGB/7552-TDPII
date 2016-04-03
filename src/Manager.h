/*
 * Manager.h
 *
 *  Created on: Mar 31, 2016
 *      Author: juanma
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include "Database.h"

class Manager {
public:
	Manager();
	virtual ~Manager();
	Database* getDatabase();
	void setDatabase(Database* db);
	string createUser(string json);

private:
	Database* db;

};

#endif /* MANAGER_H_ */
