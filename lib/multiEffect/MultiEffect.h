#ifndef _MultiEffect_INCLUDED__
#define _MultiEffect_INCLUDED__

#include <list>
#include "../utils/Observer.h"
#include "Pedal.h"

enum Change {
	SET_PATCH = 1,
	SET_PEDAL_STATE = 2
};

class MultiEffect : public Observer, public Subject {

	public:
		MultiEffect(unsigned char totalPatch, unsigned int totalPedals, Pin& firstPin);
 		unsigned char getCurrentPatch();
		unsigned char getTotalPatch();

		void nextPatch();
		void beforePatch();
		void toPatch(unsigned char patch);
		void toPatchNotNotify(unsigned char patch);

		//void activePedal(int pedal);
		//void disablePedal(int pedal);

		std::list<Pedal> * getPedals();
		std::list<Button*> getAllButtons();

		void update(Subject* subject, int& param);

	private:
		unsigned char currentPatch;
		unsigned char totalPatch;
		std::list<Pedal> pedals;

		Button * up;
		Button * down;

		void createPedals(unsigned int totalPedals, Pin& first);
		Pedal * createPedal(unsigned char buttonPin, unsigned char ledPin);
		Button * createButton(unsigned char buttonPin);

};

#endif 