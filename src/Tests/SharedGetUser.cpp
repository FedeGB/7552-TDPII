#include <gtest/gtest.h>
#include "../SharedClient/SharedManager.h"
#include "../json/json.h"


TEST(SharedGetUser,TestGetUsers) {
	SharedManager* sManager = new SharedManager();
	const Json::Value& users = sManager->getUsers();
	Json::ValueConstIterator it = users.begin();
	int max = 3;
	int act = 0;
	while(it != users.end() && act < max) {
	    const Json::Value& user = *it;
		EXPECT_STRNE(user.get("id", "").asString().c_str(), "");
		it++;
		act++;
	}
	delete sManager;
}

TEST(SharedGetUser,TestGetSpecificUser) {
	SharedManager* sManager = new SharedManager();
	Json::Value user = sManager->getUser("1");
	delete sManager;
	EXPECT_STREQ(user.get("id", "").asString().c_str(), "1");
	EXPECT_STREQ(user.get("name", "").asString().c_str(), "Janeth Doe III");
	EXPECT_STREQ(user.get("alias", "").asString().c_str(), "janedoe");
}

TEST(SharedGetUser, TestPostUser) {
	/*CURL *hnd = curl_easy_init();

	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
	curl_easy_setopt(hnd, CURLOPT_URL, "http://tp-7552-g05-sharedserver.herokuapp.com/users");

	struct curl_slist *headers = NULL;
	curl_easy_setopt(hnd, CURLOPT_VERBOSE, 1L);
	// headers = curl_slist_append(headers, "postman-token: 370eced7-a7ff-7f6b-cd2a-f7b907c9cb2c");
	// headers = curl_slist_append(headers, "cache-control: no-cache");
	headers = curl_slist_append(headers, "content-type: application/json");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\"user\":{\"alias\":\"username\",\"email\":\"aasda@sdasa.com\",\"interests\":[{\"category\":\"music/band\",\"value\":\"radiohead\"}],\"location\":{\"latitude\":23.199999999999999,\"longitude\":32.100000000000001},\"name\":\"hello there\",\"photoProfile\":null,\"sex\":\"M\"}}");

	CURLcode ret = curl_easy_perform(hnd);*/
	SharedManager* sManager = new SharedManager();
	User* user = new User("username");
	bool status = sManager->postUser(user);
	delete user;
	delete sManager;
	ASSERT_TRUE(status == 0);
}