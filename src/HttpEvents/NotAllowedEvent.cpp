#include "NotAllowedEvent.h"

void NotAllowedEvent::NotAllowedEvent() {

}

void NotAllowedEvent::~NotAllowedEvent() {

}

void NotAllowedEvent::handle() {
	this->respondNotFound();
}