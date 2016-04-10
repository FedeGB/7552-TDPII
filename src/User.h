/*
 * User.h
 *
 *  Created on: Mar 26, 2016
 *      Author: juanma
 */

#ifndef USER_H_
#define USER_H_


#include "json/json.h"

#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <string>





using namespace std;
using namespace Json;


class User {
public:
	User(string username);
	//User(Json::Value value);
	virtual ~User();

	void setName(const string& name);
	string getName();

	string getPassword();

	double getLocationX() const;
	void setLocationX(double locationX);

	double getLocationY() const;
	void setLocationY(double locationY);

	void setPassword(const string& password);

	const string& getPerfilImage() const;
	void setPerfilImage(const string& perfilImage);

	const string& getToken() const;
	void setToken(const string& token);

	const string& getUsername() const;
	void setUsername(const string& username);

	string getJsonString();
	Json::Value getJson();
	void initWithJson(Json::Value value);
	void loginNow();

private:
	string username;
	string name;
	string password;
	double locationX;
	double locationY;
	string perfilImage;
	string token;
	time_t lastTimeConnected;

};

#endif /* USER_H_ */
