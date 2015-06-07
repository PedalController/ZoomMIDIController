#ifndef _MultiEffectComunicator_INCLUDED__
#define _MultiEffectComunicator_INCLUDED__

#include "../arduinoUtils/SimuleArduino.h"
#include "../multiEffect/MultiEffect.h"
#include "../multiEffect/Pedal.h"
#include "../utils/Subject.h"
#include "Comunicator.h"

/**
 * A ponte entre a sumulação da pedaleira no arduino e 
 * o objeto o que irá enviar os dados para a pedaleira real
 */
class MultiEffectComunicator : public Comunicator {
	public:
		MultiEffectComunicator(MultiEffect* subject, Destination * destination);

		virtual void update(Subject* subject, int& parameter) final;

		// Eu vou dizer algo
		//virtual void sendMessageWait();
		// Quer me dizer alguma coisa?
		//virtual void sendMessageSendMeAnMessage();

		virtual void sendMessagePatch(MultiEffect * multiStomp) = 0;
		virtual void sendMessagePedalState(Pedal * pedal) = 0;

	protected:
		virtual void sendMessage(byte * message, int size) final;
};
	
#endif