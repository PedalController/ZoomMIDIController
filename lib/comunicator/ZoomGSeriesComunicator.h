#ifndef _ZoomGSeriesComunicator_INCLUDED__
#define _ZoomGSeriesComunicator_INCLUDED__

#include "MultiEffectComunicator.h"

class ZoomGSeriesComunicator : public MultiEffectComunicator {
	public:
		ZoomGSeriesComunicator(MultiEffect* subject, Destination * destination);

		virtual void sendMessagePatch(MultiEffect * multiStomp);
		virtual void sendMessagePedalState(Pedal * pedal);
};

#endif