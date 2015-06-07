#include "Pedal.h"

Pedal::Pedal(int position, Pin& button, Pin& led) : Button(button) {
	this->position = position;
	this->led = &led;
}

int Pedal::getPosition() {
	return this->position;
}