//
// Created by Juan Manuel Hidalgo on 26/4/16.
//

#include "LikeFactory.h"


LikeFactory::LikeFactory() {
    // TODO Auto-generated constructor stub

}

LikeFactory::~LikeFactory() {
    // TODO Auto-generated destructor stub
}


Like* LikeFactory::createWithJsonValue(Json::Value value) {
    string user1 = value.get("user1", "").asString();
    string user2 = value.get("user2","").asString();
    bool data = value.get("like", "").asBool();
    User* usr1 = new User(user1);
    User* usr2 = new User(user2);
    Like* msg = new Like(usr1, usr2, data);
    return msg;
}

Like* LikeFactory::createWithJsonString(string json) {
    Json::Reader r = Json::Reader();
    Json::Value val = Json::Value();
    r.parse(json.c_str(),val);
    return this->createWithJsonValue(val);
}
