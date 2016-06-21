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
        Json::Reader r = Json::Reader();
        Json::Value val = Json::Value();
        r.parse(hm->body.p,val);
        string userString = val.get("user1", "").asString();
        User* user = manager->getUser(userString);
        struct mg_str *cl_header = mg_get_http_header(hm, "Token");

        if(!cl_header) {
            this->response(1, "Token missing", returnEmptyJsonObject());
            return;
        }

        std::string token(getHeaderParam(cl_header->p));
        if(token.compare(user->getToken()) != 0){
            this->response(1, "Invalid Token", returnEmptyJsonObject());
            return;
        }

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
            this->response(1, "Couldn't save like", returnEmptyJsonObject());
        }
    }
}
