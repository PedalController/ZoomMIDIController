#ifndef _Pedal_INCLUDED__
#define _Pedal_INCLUDED__

#include "../arduinoUtils/Pin.h"
#include "../arduinoUtils/Button.h"

class Pedal : public Button {

	public:
		Pedal(int position, Pin& pin, Pin& led);
		int getPosition();

	private:
		Pin * led;
		int position;
};

#endif 