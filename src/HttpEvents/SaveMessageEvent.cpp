//
// Created by Juan Manuel Hidalgo on 24/4/16.
//

#include "SaveMessageEvent.h"

SaveMessageEvent::SaveMessageEvent() {

}

SaveMessageEvent::SaveMessageEvent(struct mg_connection* nco, struct http_message* hme) {
    this->nc = nco;
    this->hm = hme;
    this->methodType = "POST";
}

SaveMessageEvent::~SaveMessageEvent() {

}

bool SaveMessageEvent::validateInput() {

    bool parentValidation = EventHandler::validateInput();
    if(!parentValidation) return parentValidation;


    // Validar header y token para ver si es correcto el acceso!!!
    return true;
}

void SaveMessageEvent::handle(Manager* manager, SharedManager* sManager) {
    Json::Reader r = Json::Reader();
    Json::Value val = Json::Value();
    r.parse(hm->body.p,val);
    string userString = val.get("user1", "").asString();
    User* user = manager->getUser(userString);
    struct mg_str *cl_header = mg_get_http_header(hm, "Token");
    if(!cl_header) {
        this->response(1, "Invalid Token", Json::Value());
        return;
    }
    std::string token(getHeaderParam(cl_header->p));
    if(token.compare(user->getToken()) == 0){
        bool messageWasSaved = manager->saveMessage(hm->body.p);
        if(messageWasSaved) {
            this->response(0, "Message Saved", Json::Value());
        } else {
            this->response(1, "Couldn't save", Json::Value());
        }
    } else {
        this->response(2, "Invalid Token", Json::Value());
    }
}