#ifndef _Button_INCLUDED__
#define _Button_INCLUDED__

#include "../utils/Subject.h"
#include "Pin.h"

const int BUTTON_CHANGED = 0;

class Button : public Subject {

	public:
		Button(Pin& pin);
 		bool isActived();
		void active();
		void disable();
		void switchState();

		void update();

		friend bool operator==(Button& button1, Button& button2) {
			return button1.pin == button2.pin;
		}

		friend bool operator!=(Button& button1, Button& button2) {
			return !(button1.pin == button2.pin);
		}

		Pin * getPin();

	private:
		Pin * pin;
		bool state;
		void setState(bool newState);
};

#endif 