#include "Comunicator.h"

Comunicator::Comunicator(Subject * subject, Destination * destination) {
	subject->attach(this);
	this->destination = destination;
}

void Comunicator::notify(void * message, ...) {
	va_list args;
	va_start(args, message);

	this->destination->take(message, args);

	va_end(args);
}