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


string getToken(string header){
    string delimiter = "\r";
    int position = header.find(delimiter);
    string token = header.substr(0, position);
    return token;
}


void GetUserMatches::handle(Manager* manager, SharedManager* sManager) {
    if(this->validateInput()) {
        char user[100];
        mg_get_http_var(&hm->query_string, "user", user, sizeof(user));
        string userString = getUserFromURL(hm->uri.p);
        User* userFound = manager->getUser(userString);
        Json::Value event;
        Json::Value vec(Json::arrayValue);

        if(userFound){
            char base[100];
            struct mg_str *cl_header = mg_get_http_header(hm, "Authorization");
            //mg_get_http_var(cl_header, "ApiToken", base, sizeof(base));
            std::string token(getToken(cl_header->p));
            if(token.compare(userFound->getToken()) == 0){
                vector<string> matches = manager->getMatches(userString);
                for (int i = 0 ; i < matches.size() ; i++){
                    vec.append(matches.at(i));
                }
                event["matches"] = vec;
                std::cout << event << std::endl;


            }

        }
        this->response(0, "", event);
    }
}