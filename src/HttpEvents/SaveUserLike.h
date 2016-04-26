//
// Created by Juan Manuel Hidalgo on 26/4/16.
//

#ifndef TINDER_SAVEUSERLIKE_H
#define TINDER_SAVEUSERLIKE_H

#include "EventHandler.h"


class SaveUserLike: public EventHandler {
public:
    SaveUserLike();
    SaveUserLike(struct mg_connection*, struct http_message*);
    ~SaveUserLike();
    void handle(Manager*);

protected:
    bool validateInput();

};


#endif //TINDER_SAVEUSERLIKE_H
