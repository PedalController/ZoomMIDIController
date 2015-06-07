#include "MultiEffectComunicator.h"
#include "../multiEffect/MultiEffect.h"

MultiEffectComunicator::MultiEffectComunicator(MultiEffect* subject, Destination * destination)
: Comunicator(subject, destination) {
	
}


void MultiEffectComunicator::update(Subject* subject, int& parameter) {
	switch(parameter) {
		case SET_PATCH:
			this->sendMessagePatch((MultiEffect*) subject);
			break;
		case SET_PEDAL_STATE:
			this->sendMessagePedalState((Pedal*) subject);
			break;
	}
}

void MultiEffectComunicator::sendMessage(byte * message, int size) {
	this->notify(message, size);
}