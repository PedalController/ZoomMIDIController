#ifndef _ZoomGSeries_INCLUDED__
#define _ZoomGSeries_INCLUDED__

#include <list>
#include "MultiEffect.h"

class ZoomGSeries : public MultiEffect {
	public:
		ZoomGSeries(unsigned int totalPedals, Pin& firstPin);
};

#endif 