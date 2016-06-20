//
// Created by Juan Manuel Hidalgo on 27/4/16.
//

#include "DeleteUserEvent.h"

DeleteUserEvent::DeleteUserEvent() {
}

DeleteUserEvent::DeleteUserEvent(struct mg_connection* nco, struct http_message* hme) {
    this->nc = nco;
    this->hm = hme;
    this->methodType = "DELETE";
}

DeleteUserEvent::~DeleteUserEvent() {

}

bool DeleteUserEvent::validateInput() {
    bool parentValidation = EventHandler::validateInput();
    if(!parentValidation) return parentValidation;
    // TODO: Validate content type header is application/json

    Json::Reader r = Json::Reader();
    Json::Value val = Json::Value();
    r.parse(hm->body.p,val);
    if(val.get("username", "").asString().compare("") == 0) {
        this->response(2, "Missing parameters", Json::Value());
        return false;
    }
    return true;
}

void DeleteUserEvent::handle(Manager* manager, SharedManager* sManager) {
    bool validation = this->validateInput();
    if(validation) {
        Json::Reader r = Json::Reader();
        Json::Value val = Json::Value();
        r.parse(hm->body.p,val);
        User* userToDelete = manager->getUser(val.get("username", "").asString());
        int sharedId = userToDelete->getId();
        bool userWasDeleted = manager->deleteUser(val.get("username", "").asString());
        delete userToDelete;
        if(userWasDeleted) {
            bool userSharedDeleted = sManager->deleteUser(sharedId);
            if(userSharedDeleted) {
                this->response(0, "Deleted", Json::Value());
            } else {
                this->response(1, "Deletion was partially done", Json::Value());    
            }
        } else {
            this->response(1, "Couldnt delete user", Json::Value());
        }
    }
}