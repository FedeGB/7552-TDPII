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
    if(this->validateInput()) {
        bool messageWasSaved = manager->saveMessage(hm->body.p);
        if(messageWasSaved) {
            this->response(0, "Message Saved", (Json::Value)0);
        } else {
            this->response(1, "Couldn't save", (Json::Value)0);
        }
    }
}