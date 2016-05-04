//
// Created by Juan Manuel Hidalgo on 29/4/16.
//

#include "GetUsers.h"


GetUsers::GetUsers() {

}


GetUsers::GetUsers(struct mg_connection* nco, struct http_message* hme) {
    this->nc = nco;
    this->hm = hme;
    this->methodType = "GET";
//    if(mg_vcmp(&hme->method, "GET") == 0) {
//        this->methodType = "GET";
//    }else if(mg_vcmp(&hme->method, "POST") == 0) {
//        this->methodType = "POST";
//    }else if(mg_vcmp(&hme->method, "PUT")){
//        this->methodType = "PUT";
//    }else {
//        this->methodType = "DELETE";
//    }
//    this->parameter = getParameter(hm->uri.p);
}

GetUsers::~GetUsers() {

}

bool GetUsers::validateInput() {
    bool parentValidation = EventHandler::validateInput();
    if(!parentValidation) return parentValidation;
    // Validar header y token para ver si es correcto el acceso!!!
    return true;
}

void GetUsers::handle(Manager* manager) {
    if(this->validateInput()) { // users/    GET all users
//        if(this->parameter == "") {
            vector<Json::Value> users = manager->getAllUsers();
            Json::Value event;
            Json::Value vec(Json::arrayValue);
            for (int i = 0; i < users.size(); i++) {
                vec.append(users.at(i));
            }
            event["Users"] = vec;
            std::cout << event << std::endl;
            this->response(0, "", event);
        }
//    }else if(this->methodType == "GET"){ // users/ POST create user

}
