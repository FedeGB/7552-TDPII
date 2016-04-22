//
// Created by Juan Manuel Hidalgo on 22/4/16.
//

#include "Match.h"

Match::Match(){

}

Match::~Match() {

}

bool Match::getResult() {
    return result;
}

    void Match::setUser1(User* user) {
    user1 = user;
}


void Match::setUser2(User* user) {
    user2= user;
}

User* Match::getUser1() {
    return user1;
}

User* Match::getUser2() {
    return user2;
}