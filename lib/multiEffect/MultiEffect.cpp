#include <string>
#include "MultiEffect.h"

/******************************
 * Constructor
 ******************************/
MultiEffect::MultiEffect(unsigned char totalPatch, unsigned int totalPedals, Pin& firstPin) {
	this->totalPatch = totalPatch;
	this->toPatch(0);

	this->createPedals(totalPedals, firstPin);

  	// Botões do patch
	unsigned char pin = firstPin.getPin() + totalPedals*2;
  	this->up = this->createButton(pin);
  	this->down = this->createButton(pin+1);
}


unsigned char MultiEffect::getCurrentPatch() {
	return this->currentPatch;
}

unsigned char MultiEffect::getTotalPatch() {
	return this->totalPatch;
}

void MultiEffect::createPedals(unsigned int totalPedals, Pin& first) {
	Pedal * pedal;
	unsigned char firstPin = first.getPin();
	unsigned int positionPedal;

	for (positionPedal=firstPin; positionPedal < firstPin+totalPedals*2; positionPedal+=2) {
		pedal = this->createPedal(positionPedal, positionPedal+1);

		pedal->attach(this);
		this->pedals.push_back(*pedal);
	}
}

Pedal * MultiEffect::createPedal(unsigned char buttonPin, unsigned char ledPin) {
	Pin * button = new Pin(buttonPin);
	Pin * led = new Pin(ledPin);

	return new Pedal(this->pedals.size(), *button, *led);
}

Button * MultiEffect::createButton(unsigned char buttonPin) {
	Pin * pin = new Pin(buttonPin);
	return new Button(*pin);
}

/******************************
 * Controlling
 *******************************/
void MultiEffect::nextPatch() {
	unsigned char patch = this->currentPatch;
  	if (currentPatch == this->totalPatch-1)
      	patch = 0;
	else 
		patch++;

	this->MultiEffect::toPatch(patch);
}

void MultiEffect::beforePatch() {
	unsigned char patch = this->currentPatch;
  	if (currentPatch == 0)
      	patch = this->totalPatch-1;
	else 
		patch--;

	this->MultiEffect::toPatch(patch);
}

void MultiEffect::toPatch(unsigned char patch) {
	if (patch < 0 || patch >= this->totalPatch)
		return;

	this->toPatchNotNotify(patch);
	this->notify(SET_PATCH);
}

/** Update patch and not comunicate the Physical MultiEffect
 */
void MultiEffect::toPatchNotNotify(unsigned char patch) {
	this->currentPatch = patch;
}

/******************************
 * Access the phisical elements
 *******************************/
std::list<Pedal> * MultiEffect::getPedals() {
	return &this->pedals;
}

std::list<Button*> MultiEffect::getAllButtons() {
	std::list<Button*> buttons;

	buttons.push_back(this->up);
	buttons.push_back(this->down);

	for (Pedal& pedal: this->pedals)
        buttons.push_back(&pedal);

	return buttons;
}

/******************************
 * Observer Pattern
 *******************************/
void MultiEffect::update(Subject* subject, int& param) {
	if (param == BUTTON_CHANGED)
		param = SET_PEDAL_STATE;

	this->notify(subject, param);
}