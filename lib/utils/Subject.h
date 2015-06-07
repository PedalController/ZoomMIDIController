#ifndef _Subject_INCLUDED__
#define _Subject_INCLUDED__

#include <vector>
#include "Observer.h"

class Observer;

class Subject {
	public:
		virtual void attach(Observer * observer) final;
		virtual void notify(int param) final;
		virtual void notify(Subject * element, int param) final;

	private:
		std::vector<class Observer *> views;
};

#endif