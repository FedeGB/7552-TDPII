//
// Created by Juan Manuel Hidalgo on 24/4/16.
//

#ifndef TINDER_SAVEMESSAGEEVENT_H
#define TINDER_SAVEMESSAGEEVENT_H

#include "EventHandler.h"


class SaveMessageEvent: public EventHandler {
public:
    SaveMessageEvent();
    SaveMessageEvent(struct mg_connection*, struct http_message*);
    ~SaveMessageEvent();
    void handle(Manager*, SharedManager*);

protected:
    bool validateInput();

};


#endif //TINDER_SAVEMESSAGEEVENT_H

