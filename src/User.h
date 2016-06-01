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
	virtual ~User();

	void setName(string name);
	string getName();

	string getPassword();

	double getLatitude();
	void setLatitude(double locationX);

	double getLongitude();
	void setLongitude(double locationY);

	void setPassword(string password);

	// string getPerfilImage();
	// void setPerfilImage(string perfilImage);

	string getToken();
	void setToken(string token);

	void setId(int);
	int getId();

	string getUsername();
	void setUsername(string username);

	string getEmail();
	void setEmail(string);

	string getJsonString();

	// Devuelve los datos del usuario en un Json
	// No se devuelve Password ni token
	// El que recibe un booleano se le puede indicar si
	// Se quiere que se devuelva la data del usuario sin Matches
	Json::Value getJson();
	Json::Value getJson(bool);

	void initWithJson(Json::Value value);
	void updateWithJson(Json::Value value);
	void loginNow();

	vector<string> getMatches();
	void setMatches(vector<string> vector);
	void addMatch(string user);


private:
	int id;
	string username;
	string name;
	string email;
	string password;
	double latitude;
	double longitude;
	// string perfilImage;
	string token;
	time_t lastTimeConnected;
	vector<string> matches;

};

#endif /* USER_H_ */
