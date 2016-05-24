#include "NotAllowedEvent.h"

NotAllowedEvent::NotAllowedEvent() {

}

NotAllowedEvent::NotAllowedEvent(struct mg_connection* nco, struct http_message* hme) {
    this->nc = nco;
    this->hm = hme;
    this->methodType = "";
}

NotAllowedEvent::~NotAllowedEvent() {

}

void NotAllowedEvent::handle(Manager* manager, SharedManager* sManager) {
	this->respondNotFound();
}