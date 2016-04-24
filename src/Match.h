//
// Created by Juan Manuel Hidalgo on 22/4/16.
//

#ifndef TINDER_MATCH_H
#define TINDER_MATCH_H

#include "User.h"

class Match {
public:
    Match();
    ~Match();
    bool getResult();
    void setUser1(User* user);
    void setUser2(User* user);
    User* getUser1();
    User* getUser2();

private:
    //User* matches[];
    User* user1;
    User* user2;
    bool result;

};


#endif //TINDER_MATCH_H
