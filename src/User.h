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

	double getLatitude() const;
	void setLatitude(double locationX);

	double getLongitude() const;
	void setLongitude(double locationY);

	void setPassword(const string& password);

	const string& getPerfilImage() const;
	void setPerfilImage(const string& perfilImage);

	const string& getToken() const;
	void setToken(const string& token);

	const string& getUsername() const;
	void setUsername(const string& username);

	const string& getEmail();
	void setEmail(string);

	string getJsonString();
	Json::Value getJson();
	void initWithJson(Json::Value value);
	void loginNow();

	vector<string> getMatches();
	void setMatches(vector<string> vector);
	void addMatch(string user);


private:
	string username;
	string name;
	string email;
	string password;
	double latitude;
	double longitude;
	string perfilImage;
	string token;
	time_t lastTimeConnected;
	vector<string> matches;

};

#endif /* USER_H_ */
