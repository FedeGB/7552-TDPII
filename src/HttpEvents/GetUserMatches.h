//
// Created by Juan Manuel Hidalgo on 26/4/16.
//

#ifndef TINDER_GETUSERMATCHES_H
#define TINDER_GETUSERMATCHES_H


#include "EventHandler.h"


class GetUserMatches : public EventHandler {
public:
    GetUserMatches();
    GetUserMatches(struct mg_connection*, struct http_message*);
    ~GetUserMatches();
    void handle(Manager*);

protected:
    bool validateInput();
};

#endif //TINDER_GETUSERMATCHES_H
