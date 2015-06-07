#ifndef _Pin_INCLUDED__
#define _Pin_INCLUDED__

class Pin {

	public:
		Pin(unsigned char pin);
		unsigned char getPin(void);

	private:
		unsigned char pin;
};

#endif 