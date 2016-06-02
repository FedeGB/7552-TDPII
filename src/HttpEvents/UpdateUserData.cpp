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

void UpdateUserData::handle(Manager* manager, SharedManager* sManager) {
    //bool validation = this->validateInput();
    //if(validation) {
    Json::Reader r = Json::Reader();
    Json::Value value = Json::Value();
    r.parse(hm->body.p, value);
    // Local user update
    User* user = manager->getUser(value.get("username","").asString());
    user->updateWithJson(value);
    bool updateUser = manager->updateUser(user);
    if(updateUser) {
        value["id"] = user->getId();
        if(value.isMember("photoProfile") || value.isMember("photo_profile")) {
            // Photo Profile Upload
            std::string key = "";
            value.isMember("photoProfile") ? key = "photoProfile" : key = "photo_profile";
            Json::Value uploadP = Json::Value();
            uploadP["photo"] = value.get(key, "").asString();
            uploadP["id"] = user->getId();
            value.removeMember(key);
            int photoUp = sManager->putUserPhoto(uploadP);
            if(!photoUp) {
                this->response(1, "User photo profile could not be uploaded", (Json::Value)0);
                return;
            }
        }
        // Rest of user data to update on Shared Server
        int sharedUpdate = sManager->putUser(value);
        if(sharedUpdate) {
            this->response(0, "Modified", user->getJson());
        } else {
            this->response(1, "User could not be modified", (Json::Value)0);
        }
    } else {
        this->response(1, "User could not be modified", (Json::Value)0);
    }
    delete user;
}