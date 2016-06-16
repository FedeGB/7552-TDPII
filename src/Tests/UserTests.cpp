#include <gtest/gtest.h>
#include "../User.h"
#include "../Factories/UserFactory.h"



TEST(UsersTests,TestNewUser){
	string user1 = "User1";
	User* user = new User(user1);
	user->setPassword("hola");
	user->setName("Juan");
	user->setLatitude(20.0);
	user->setLongitude(40.0);
	// user->setPerfilImage("URL");
	ASSERT_EQ("User1", user->getUsername());
	ASSERT_EQ("hola", user->getPassword());
	ASSERT_EQ("Juan", user->getName());
	ASSERT_EQ(20.0, user->getLatitude());
	ASSERT_EQ(40.0, user->getLongitude());
	// ASSERT_EQ("URL", user->getPerfilImage());
	delete user;
}




TEST(UsersTests, TestJson){
	User* user = new User("User1");
	Json::Value value;
	value["name"] = "User 1";
	value["email"] = "user1@mail.com";
	value["password"] = "123456";
	Json::Value location = Json::Value();
	location["latitude"] = 10.50;
	location["longitude"] = -1.5897;
	value["location"] = location;
	value["distance"] = 5;
	Json::Value range = Json::Value();
	range["min"] = 20;
	range["max"] = 24;
	value["ageRange"] = range;
	user->initWithJson(value);
	Json::Value userComp = user->getJson(false);
	ASSERT_EQ(userComp.get("email", "").asString(), value.get("email", "").asString());
	ASSERT_EQ(userComp.get("password", "").asString(), value.get("password", "").asString());
	ASSERT_EQ(userComp.get("distance", "").asDouble(), value.get("distance", "").asDouble());
	ASSERT_EQ(userComp.get("location", Json::Value()).get("latitude", 0).asDouble(),
	 value.get("location", Json::Value()).get("latitude", 0).asDouble());
	ASSERT_EQ(userComp.get("location", Json::Value()).get("longitude", 0).asDouble(),
	 value.get("location", Json::Value()).get("longitude", 0).asDouble());
	ASSERT_EQ(userComp.get("ageRange", Json::Value()).get("min", 0).asInt(),
	 value.get("ageRange", Json::Value()).get("min", 0).asInt());
	ASSERT_EQ(userComp.get("ageRange", Json::Value()).get("max", 0).asInt(),
	 value.get("ageRange", Json::Value()).get("max", 0).asInt());
	delete user;
}


TEST(UsersTests, TestJsonUpadate){
	User* user = new User("User1");
	Json::Value value;
	value["name"] = "User 1";
	value["email"] = "user1@mail.com";
	value["password"] = "123456";
	Json::Value location = Json::Value();
	location["latitude"] = 10.50;
	location["longitude"] = -1.5897;
	value["location"] = location;
	value["distance"] = 5;
	Json::Value range = Json::Value();
	range["min"] = 20;
	range["max"] = 24;
	value["ageRange"] = range;
	user->initWithJson(value);
	// Updates
	value["distance"] = 10;
	range["min"] = 18;
	value["ageRange"] = range;
	location["latitude"] = 2.333;
	value["location"] = location;
	user->updateWithJson(value);
	Json::Value userComp = user->getJson(false);
	ASSERT_EQ(userComp.get("email", "").asString(), value.get("email", "").asString());
	ASSERT_EQ(userComp.get("password", "").asString(), value.get("password", "").asString());
	ASSERT_EQ(userComp.get("distance", "").asDouble(), value.get("distance", "").asDouble());
	ASSERT_EQ(userComp.get("location", Json::Value()).get("latitude", 0).asDouble(),
	 value.get("location", Json::Value()).get("latitude", 0).asDouble());
	ASSERT_EQ(userComp.get("location", Json::Value()).get("longitude", 0).asDouble(),
	 value.get("location", Json::Value()).get("longitude", 0).asDouble());
	ASSERT_EQ(userComp.get("ageRange", Json::Value()).get("min", 0).asInt(),
	 value.get("ageRange", Json::Value()).get("min", 0).asInt());
	ASSERT_EQ(userComp.get("ageRange", Json::Value()).get("max", 0).asInt(),
	 value.get("ageRange", Json::Value()).get("max", 0).asInt());

	ASSERT_NE(userComp.get("distance", "").asDouble(), 5);
	ASSERT_NE(userComp.get("location", Json::Value()).get("latitude", 0).asDouble(), 10.50);
	ASSERT_NE(userComp.get("ageRange", Json::Value()).get("min", 0).asInt(), 20);
	delete user;
}


TEST(UsersTests, TestUserFactoryNomal) {
	UserFactory factory;
	User* u1 = factory.createUser("user1", "123456");
	ASSERT_EQ(u1->getUsername(), "user1");
	ASSERT_EQ(u1->getPassword(), "123456");
	ASSERT_EQ(u1->getLongitude(), 0);
	ASSERT_EQ(u1->getDistance(), 10);
	delete u1;
}


TEST(UsersTests, TestUserFactoryJsonValue) {
	UserFactory factory;
	Json::Value value;
	value["username"] = "User1";
	value["name"] = "User 1";
	value["email"] = "user1@mail.com";
	value["password"] = "123456";
	Json::Value location = Json::Value();
	location["latitude"] = 10.50;
	location["longitude"] = -1.5897;
	value["location"] = location;
	value["distance"] = 5;
	Json::Value range = Json::Value();
	range["min"] = 20;
	range["max"] = 24;
	value["ageRange"] = range;
	User* u1 = factory.createWithJsonValue(value);
	Json::Value userComp = u1->getJson(false);
	ASSERT_EQ(userComp.get("username", "").asString(), value.get("username", "").asString());
	ASSERT_EQ(userComp.get("email", "").asString(), value.get("email", "").asString());
	ASSERT_EQ(userComp.get("password", "").asString(), value.get("password", "").asString());
	ASSERT_EQ(userComp.get("distance", "").asDouble(), value.get("distance", "").asDouble());
	ASSERT_EQ(userComp.get("location", Json::Value()).get("latitude", 0).asDouble(),
	 value.get("location", Json::Value()).get("latitude", 0).asDouble());
	ASSERT_EQ(userComp.get("location", Json::Value()).get("longitude", 0).asDouble(),
	 value.get("location", Json::Value()).get("longitude", 0).asDouble());
	ASSERT_EQ(userComp.get("ageRange", Json::Value()).get("min", 0).asInt(),
	 value.get("ageRange", Json::Value()).get("min", 0).asInt());
	ASSERT_EQ(userComp.get("ageRange", Json::Value()).get("max", 0).asInt(),
	 value.get("ageRange", Json::Value()).get("max", 0).asInt());
	delete u1;
}

TEST(UsersTests, TestUserFactoryJsonString) {
	UserFactory factory;
	Json::Value value;
	value["username"] = "User1";
	value["name"] = "User 1";
	value["email"] = "User1";
	value["password"] = "123456";
	Json::Value location = Json::Value();
	location["latitude"] = 10.50;
	location["longitude"] = -1.5897;
	value["location"] = location;
	value["distance"] = 5;
	Json::Value range = Json::Value();
	range["min"] = 20;
	range["max"] = 24;
	value["ageRange"] = range;
	Json::FastWriter fast;
	std::string json = fast.write(value);
	User* u1 = factory.createWithJsonString(json);
	Json::Value userComp = u1->getJson(false);
	ASSERT_EQ(userComp.get("username", "").asString(), value.get("username", "").asString());
	ASSERT_EQ(userComp.get("email", "").asString(), value.get("email", "").asString());
	ASSERT_EQ(userComp.get("password", "").asString(), value.get("password", "").asString());
	ASSERT_EQ(userComp.get("distance", "").asDouble(), value.get("distance", "").asDouble());
	ASSERT_EQ(userComp.get("location", Json::Value()).get("latitude", 0).asDouble(),
	 value.get("location", Json::Value()).get("latitude", 0).asDouble());
	ASSERT_EQ(userComp.get("location", Json::Value()).get("longitude", 0).asDouble(),
	 value.get("location", Json::Value()).get("longitude", 0).asDouble());
	ASSERT_EQ(userComp.get("ageRange", Json::Value()).get("min", 0).asInt(),
	 value.get("ageRange", Json::Value()).get("min", 0).asInt());
	ASSERT_EQ(userComp.get("ageRange", Json::Value()).get("max", 0).asInt(),
	 value.get("ageRange", Json::Value()).get("max", 0).asInt());
	delete u1;
}