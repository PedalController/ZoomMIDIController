#include "Pin.h"

Pin::Pin(unsigned char pin) {
	this->pin = pin;
}

unsigned char Pin::getPin(void) {
	return this->pin;
}