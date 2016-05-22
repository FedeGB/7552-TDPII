#include <gtest/gtest.h>
#include "../SharedClient/SharedManager.h"
#include "../json/json.h"


void get_random_str(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

	srand(time(NULL));
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

TEST(SharedInterestTests, TestPostInterest) {
	SharedManager* sManager = new SharedManager();
	Json::Value interestJson = Json::Value();
	interestJson["category"] = "music/band";
	char* value = new char[10]();
	get_random_str(value, 9);
	interestJson["value"] = value;
	bool response = sManager->postInterest(interestJson);
	delete[] value;
	ASSERT_TRUE(response);
}

TEST(SharedInterestTests, TestGetInterests) {
	SharedManager* sManager = new SharedManager();
	const Json::Value& interests = sManager->getInterests();
	Json::ValueConstIterator it = interests.begin();
	int max = 20;
	int act = 0;
	while(it != interests.end() && act < max) {
	    const Json::Value& interest = *it;
		EXPECT_STRNE(interest.get("value", "").asString().c_str(), "");
		it++;
		act++;
	}
	delete sManager;
}