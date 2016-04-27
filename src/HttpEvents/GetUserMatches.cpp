//
// Created by Juan Manuel Hidalgo on 26/4/16.
//

#include "GetUserMatches.h"



GetUserMatches::GetUserMatches() {

}

GetUserMatches::GetUserMatches(struct mg_connection* nco, struct http_message* hme) {
    this->nc = nco;
    this->hm = hme;
    this->methodType = "GET";
}

GetUserMatches::~GetUserMatches() {

}

bool GetUserMatches::validateInput() {

    bool parentValidation = EventHandler::validateInput();
    if(!parentValidation) return parentValidation;
    // Validar header y token para ver si es correcto el acceso!!!
    return true;
}

void GetUserMatches::handle(Manager* manager) {
    if(this->validateInput()) {
        char user[100];
        mg_get_http_var(&hm->query_string, "user", user, sizeof(user));
        std::string user1Str(user);
        vector<string> matches = manager->getMatches(user);
        Json::Value event;
        Json::Value vec(Json::arrayValue);
        for (int i = 0 ; i < matches.size() ; i++){
            vec.append(matches.at(i));
        }
        event["matches"] = vec;
        std::cout << event << std::endl;

        this->response(0, "", event);
    }
}