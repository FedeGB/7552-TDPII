//
// Created by Juan Manuel Hidalgo on 29/4/16.
//

#ifndef TINDER_GETUSERS_H
#define TINDER_GETUSERS_H

#include "EventHandler.h"

class GetUsers: public EventHandler {
public:
    GetUsers();
    GetUsers(struct mg_connection*, struct http_message*);
    ~GetUsers();
    void handle(Manager*, SharedManager*);

protected:
    bool validateInput();
    string parameter;
};


#endif //TINDER_GETUSERS_H
