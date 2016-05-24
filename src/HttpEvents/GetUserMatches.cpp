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

string getUserFromURL(string url){
    url = url.substr(1, url.length());
    string delimiter = "users/";
    int position = url.find(delimiter);
    int positionSpace = url.find("/matches");
    string token = url.substr(6, positionSpace-6);
    return token;
}

void GetUserMatches::handle(Manager* manager, SharedManager* sManager) {
    if(this->validateInput()) {
        char user[100];
        mg_get_http_var(&hm->query_string, "user", user, sizeof(user));
        std::string user1Str(user);
        string user2 = getUserFromURL(hm->uri.p);
        vector<string> matches = manager->getMatches(user2);
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