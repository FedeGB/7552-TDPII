//
// Created by Juan Manuel Hidalgo on 26/4/16.
//

#include "Like.h"

Like::Like(User *user1, User *user2, bool answer) {
    this->like = answer;
    this->user1 = user1;
    this->user2 = user2;

}

Like::Like(Json::Value value ) {
    User* user1 = new User(value.get("user1","").asString());
    this->user1 = user1;
    User* user2 = new User(value.get("user2","").asString());
    this->user2 = user2;
    this->like = value.get("like", false).asBool();

}

Like::~Like() {
}


User* Like::getUser1() {
    return user1;
}

void Like::setUser1(User *user1) {
    Like::user1 = user1;
}

User* Like::getUser2() {
    return user2;
}

void Like::setUser2(User *user2) {
    Like::user2 = user2;
}

bool Like::getLike() {
    return this->like;
}

void Like::setLike(bool like) {
    Like::like = like;
}


string Like::getJsonString() {
    Json::StreamWriterBuilder builder;
    builder.settings_["identation"] = "\t";
    return Json::writeString(builder,this->getJson());
}

Json::Value Like::getJson() {
    Json::Value value(Json::objectValue);
    value["user1"] = this->user1->getUsername();
    value["user2"] = this->user2->getUsername();
    value["like"] = this->like;
    return value;
}