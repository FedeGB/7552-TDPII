//
// Created by Juan Manuel Hidalgo on 1/5/16.
//

#ifndef TINDER_UPDATEUSERDATA_H
#define TINDER_UPDATEUSERDATA_H


#include "EventHandler.h"

class UpdateUserData : public EventHandler {
public:
    UpdateUserData();
    UpdateUserData(struct mg_connection*, struct http_message*, string parameter);
    ~UpdateUserData();
    void handle(Manager*, SharedManager*);

protected:
    bool validateInput();
    string parameter;


};


#endif //TINDER_UPDATEUSERDATA_H
