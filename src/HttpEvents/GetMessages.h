//
// Created by Juan Manuel Hidalgo on 14/5/16.
//

#ifndef TINDER_GETMESSAGES_H
#define TINDER_GETMESSAGES_H


#include "EventHandler.h"

class GetMessages : public EventHandler {
public:
    GetMessages();
    GetMessages(struct mg_connection*, struct http_message*);
    ~GetMessages();
    void handle(Manager*, SharedManager*);

protected:
    bool validateInput();
    string parameter;

};


#endif //TINDER_GETMESSAGES_H
