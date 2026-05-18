#pragma once
#ifndef FIFO_IF_H
#define FIFO_IF_H
//interface.h
#include <systemc.h>
using namespace std;

class fifo_if : public sc_core::sc_interface
{
public:
	// Interface no longer exposes events. Buffer will handle internal
	// synchronization (not_empty / not_full) so producers/consumers don't
	// dereference the port to access events.
	virtual void write(int data) = 0;
	virtual int read() = 0;
	virtual int empty() = 0;
	virtual int size() = 0;
	virtual sc_event* data_available() = 0; // New method to check if data is available for reading
	virtual sc_event* space_available() = 0; // New method to check if space is available for writing
	virtual int capacity() = 0; // New method to get the maximum capacity of the buffer

	 fifo_if() {}
	virtual ~fifo_if() {}


};
#endif