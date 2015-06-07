#include <vector>
#include "Subject.h"
#include "Observer.h"

void Subject::attach(Observer * observer) {
	this->views.push_back(observer);
}

void Subject::notify(int param) {
	this->notify(this, param);
}

void Subject::notify(Subject * element, int param) {
	for (unsigned int i = 0; i < this->views.size(); i++)
		this->views[i]->update(element, param);
}