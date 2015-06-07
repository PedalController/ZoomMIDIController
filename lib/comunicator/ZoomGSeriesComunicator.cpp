#include "ZoomGSeriesComunicator.h"

#define POSITION_PATCH 1

#define POSICAO_PEDAL 7
#define POSICAO_LIGA_DESLIGA 10

ZoomGSeriesComunicator::ZoomGSeriesComunicator(MultiEffect* subject, Destination * destination)
: MultiEffectComunicator(subject, destination) {
	
}

void ZoomGSeriesComunicator::sendMessagePatch(MultiEffect* multiStomp) {
	byte message[2] = {
		0xC0, 0x00
	};

	message[POSITION_PATCH] = multiStomp->getCurrentPatch();

	this->sendMessage(message, 2);
}

void ZoomGSeriesComunicator::sendMessagePedalState(Pedal* pedal) {
	byte message[16] = {
		0x04, 0xF0, 0x52, 0x00,
		0x04, 0x5A, 0x31, 0x00,
		0x04, 0x00, 0x00, 0x00,
		0x05, 0xF7, 0x53, 0x00
	};

  	message[POSICAO_PEDAL] = pedal->getPosition();
	message[POSICAO_LIGA_DESLIGA] = (int) pedal->isActived();

  	this->sendMessage(message, 16);
}