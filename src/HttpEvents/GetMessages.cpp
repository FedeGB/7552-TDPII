//
// Created by Juan Manuel Hidalgo on 14/5/16.
//

#include "GetMessages.h"

GetMessages::GetMessages() {

}


GetMessages::GetMessages(struct mg_connection* nco, struct http_message* hme) {
    this->nc = nco;
    this->hm = hme;
    this->methodType = "GET";
}

GetMessages::~GetMessages() {

}

bool GetMessages::validateInput() {
    bool parentValidation = EventHandler::validateInput();
    if(!parentValidation) return parentValidation;
    // Validar header y token para ver si es correcto el acceso!!!
    return true;
}

void GetMessages::handle(Manager* manager) {
    if(this->validateInput()) { // users/    GET all users
        vector<Json::Value> messages = manager->getAllMessages();
        Json::Value event;
        Json::Value vec(Json::arrayValue);
        for (int i = 0; i < messages.size(); i++) {
            vec.append(messages.at(i));
        }
        event["messages"] = vec;
        std::cout << event << std::endl;
        this->response(0, "", event);
    }
//    }else if(this->methodType == "GET"){ // users/ POST create user

}
