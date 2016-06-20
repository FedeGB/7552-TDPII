//
// Created by Juan Manuel Hidalgo on 26/4/16.
//

#include "SaveUserLike.h"


SaveUserLike::SaveUserLike() {

}

SaveUserLike::SaveUserLike(struct mg_connection* nco, struct http_message* hme) {
    this->nc = nco;
    this->hm = hme;
    this->methodType = "POST";
}

SaveUserLike::~SaveUserLike() {

}

bool SaveUserLike::validateInput() {

    bool parentValidation = EventHandler::validateInput();
    if(!parentValidation) return parentValidation;
    // Validar header y token para ver si es correcto el acceso!!!
    return true;
}

void SaveUserLike::handle(Manager* manager, SharedManager* sManager) {
    if(this->validateInput()) {
        bool likeWasSaved = manager->saveLike(hm->body.p);
        if(likeWasSaved) {
	    	Json::Value event;
            if (manager->thereIsMatch(hm->body.p)) {
        		event["match"] = true;
            } else {
                event["match"] = false;
            }
    		this->response(0, "Like Saved", event);
        } else {
            this->response(1, "Couldn't save like", Json::Value());
        }
    }
}
