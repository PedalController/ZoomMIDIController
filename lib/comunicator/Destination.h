#ifndef _Destination_INCLUDED__
#define _Destination_INCLUDED__

class Destination {	
	public:
		virtual void take(void * message, va_list args) = 0;
};

#endif