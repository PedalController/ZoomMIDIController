#ifndef _Sender_INCLUDED__
#define _Sender_INCLUDED__

#include <cstdarg>
#include "../comunicator/Destination.h"

/** Sender envia a mensagem que recebeu para a pedaleira
 */
class Sender : public Destination {
	public:
		virtual void take(void * message, va_list args);
};

#endif