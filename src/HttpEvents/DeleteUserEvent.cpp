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
    //std::cout << val.get("password", "").asString() << std::endl;
    if(val.get("username", "").asString().compare("") == 0) {
        this->response(2, "Missing parameters", (Json::Value)0);
        return false;
    }
    return true;
}

void DeleteUserEvent::handle(Manager* manager) {
    //bool validation = this->validateInput();
    //if(validation) { // TODO add validation
        char user1[100];
        mg_get_http_var(&hm->query_string, "username", user1, sizeof(user1));
        std::string user1Str(user1);
        bool userWasDeleted = manager->deleteUser(user1Str);
        if(userWasDeleted) {
            this->response(0, "Deleted", (Json::Value)0);
        } else {
            this->response(1, "Couldnt delete user", (Json::Value)0);
        }
    //}
}