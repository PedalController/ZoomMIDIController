//http://sourcemaking.com/design_patterns/observer/cpp/3

#ifndef _Observer_INCLUDED__
#define _Observer_INCLUDED__

#include "Subject.h"

class Subject;

class Observer {
	public:
		virtual void update(Subject* subject, int& parameter) = 0;
};

#endif