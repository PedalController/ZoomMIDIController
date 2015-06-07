#ifndef _Save_INCLUDED__
#define _Save_INCLUDED__

#include "../arduinoUtils/SimuleArduino.h"
#include "../multiEffect/MultiEffect.h"
//http://playground.arduino.cc/Code/EEPROMWriteAnything
//http://www.nongnu.org/avr-libc/user-manual/group__avr__eeprom.html


// 3 bytes
typedef struct {
	byte totalPatch;
	byte currentPatch;
	byte firstPin;
	byte totalPedals;
} MultiEffectTableStruct;

typedef struct {
	byte isActived;
	byte isButtonActived;
} PedalTableStruct;

/*
typedef struct {
	UINT isActived : 1;
	UINT isButtonActived : 1;
} PedalTableStruct;
*/

/** Save and load an Multieffect
 */
class MultiEffectDao {
	public:
		static MultiEffect * load();
		static void save(MultiEffect * multiStomp);

	private:
		static void loadMultiEffect(MultiEffect * multiStomp, MultiEffectTableStruct * multiStompStruct);
		//static void loadPedals(MultiEffect * multiStomp, MultiEffectTableStruct * multiStompStruct);
		//static void loadPedal(MultiEffect * multiStomp, MultiEffectTableStruct * multiStompStruct);

		static void convertMultiEffect(MultiEffect * multiStomp, MultiEffectTableStruct * multiStompStruct);
		static void convertPedals(std::list<Pedal> * pedals, PedalTableStruct * pedalsStruct);
		static void convertPedal(Pedal * pedal, PedalTableStruct * pedalStruct);
};

#endif