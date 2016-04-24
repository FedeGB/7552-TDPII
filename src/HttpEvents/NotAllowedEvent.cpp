#include "NotAllowedEvent.h"

NotAllowedEvent::NotAllowedEvent() {

}

NotAllowedEvent::~NotAllowedEvent() {

}

void NotAllowedEvent::handle(Manager* manager) {
	this->respondNotFound();
}