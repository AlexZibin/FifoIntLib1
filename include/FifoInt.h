#ifndef FifoInt_h
#define FifoInt_h

// version: 1.0.1
// #include "Arduino.h"

typedef int fif_t;

class Fifo {
	public:
		Fifo (int size);
		Fifo (fif_t *sample, int size);
		void in (fif_t val);
		fif_t out ();	
		int size ();
		int count ();
		bool isFull ();
		bool isEmpty ();
		bool allEqual ();
		float average ();
	private:
		int _size, _count, _inPtr, _outPtr;
		fif_t *_buf;
		void increase (int *ptr);
};

#endif
