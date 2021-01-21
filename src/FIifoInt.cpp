#include "FifoInt.h"

Fifo::Fifo (int size) {
	_size = size;
	_buf = new fif_t[_size];
	_inPtr = _outPtr = _count = 0;
}

Fifo::Fifo (fif_t *sample, int size) {
	_size = _count = size;
	_buf = sample;
	_inPtr = _outPtr = 0;
}

void Fifo::in (fif_t val) {
	_buf[_inPtr] = val;
	increase (&_inPtr);
		
	if (++_count > _size) {
		_count = _size;
		increase (&_outPtr);
	}
}

void Fifo::increase (int *ptr) { if ( ++*ptr == _size) *ptr = 0; }

float Fifo::average (void) {
	if (isFull ()) {
		float sum = 0;
		for (int i = 0; i < _size; i++)
			sum += _buf[i];
		return sum/_size;
	} 
	else
		return -1;
}

fif_t Fifo::out () {
	if (!isEmpty ()) {
		fif_t retval = _buf[_outPtr];
		increase (&_outPtr);
		--_count;
		
		return retval;
	}
	else return -1;
}

int Fifo::size () {
	return _size;
}

int Fifo::count () {
	return _count;
}

bool Fifo::isFull () { return _count >= _size; }

bool Fifo::isEmpty () { return _count == 0; }

bool Fifo::allEqual () {
	if (_count < _size) return false;
	
	for (int i = 0; i < _size-1; i++)
		if (_buf[i] != _buf[i+1]) 
			return false;
		
	return true;
}
