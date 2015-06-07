#include "Button.h"

/******************************
 * Constructor
 ******************************/

Button::Button(Pin& pin) {
	this->pin = &pin;
}


/******************************
 * Controlling
 *******************************/
/** Verif if the state has changed
 */
bool Button::isActived() {
	return this->state;
}

void Button::active() {
	this->setState(true);
}

void Button::disable() {
	this->setState(false);
}

void Button::switchState() {
	this->setState(!this->state);
}

void Button::setState(bool newState) {
	this->state = newState;

	//FIXME - digitalWrite(this->pin, this->state);
	notify(BUTTON_CHANGED);
}



/******************************
 * Controlling
 *******************************/
Pin * Button::getPin() {
	return this->pin;
}