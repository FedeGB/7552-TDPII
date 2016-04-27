//
// Created by Juan Manuel Hidalgo on 26/4/16.
//

#ifndef TINDER_LIKE_H
#define TINDER_LIKE_H

#include "User.h"

class Like {
public:
    Like(User* user1, User* user2, bool like);
    Like(Json::Value value );
    ~Like();
    User* getUser1();
    User* getUser2();
    bool getLike();
    void setUser1(User* user1);
    void setUser2(User* user2);
    void setLike(bool like);
    string getJsonString();
    Json::Value getJson();


private:
    User* user1;
    User* user2;
    bool like;

};


#endif //TINDER_LIKE_H
