//
// Created by Juan Manuel Hidalgo on 1/5/16.
//

#include "UpdateUserData.h"


UpdateUserData::UpdateUserData() {

}

UpdateUserData::UpdateUserData(struct mg_connection* nco, struct http_message* hme, string parameter) {
    this->nc = nco;
    this->hm = hme;
    this->methodType = "PUT";
    this->parameter = parameter;
}

UpdateUserData::~UpdateUserData() {

}

bool UpdateUserData::validateInput() {
    bool parentValidation = EventHandler::validateInput();
    if(!parentValidation) return parentValidation;
    // TODO VALIDATE HEADER Y TOKEN
    char username[100];
    mg_get_http_var(&hm->query_string, "username", username, sizeof(username));
    std::string userStr(username);
    if(userStr.empty()) {
        this->response(2, "Missing parameters", (Json::Value)0);
        return false;
    }
    return true;
}

void UpdateUserData::handle(Manager* manager) {
    //bool validation = this->validateInput();
    //if(validation) {
    char name[100], latitude[100], longitude[100], perfilImage[100], username[100];
    mg_get_http_var(&hm->query_string, "username", username, sizeof(username));
    mg_get_http_var(&hm->query_string, "latitud", latitude, sizeof(latitude));
    mg_get_http_var(&hm->query_string, "longitud", longitude, sizeof(longitude));
    mg_get_http_var(&hm->query_string, "name", name, sizeof(name));

    User* user = manager->getUser(this->parameter);
    Json::Value value(Json::objectValue);
    value["username"] = username;
    //value["password"] = this->password;
    value["name"] = name;
    //value["token"] = ;
    value["latitud"] = latitude;
    value["longitude"] = longitude;
    value["perfilImage"] = perfilImage;
    user->initWithJson(value);
    this->response(0, "Modified", user->getJson());

}