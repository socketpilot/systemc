#pragma once
#ifndef BUFFER_H
#define BUFFER_H
#include <systemc.h>
#include <queue>
#include "interface.h"
//buffer.h
class Buffer : public sc_core::sc_module, public fifo_if
{	
public:
	sc_export<fifo_if> fifo_export; // Export the fifo interface to connect with producer and consumer
    std::queue<int> q;
	sc_event not_empty; // Event to notify when data is written to the buffer
	sc_event not_full;  // Event to notify when data is read from the buffer
    const int MAX_SIZE = 25;

    void write(int data)
    {
        if (q.empty())
        {
            q.push(data);
            not_empty.notify(); // Notify the consumer that data is available for reading
        }
        else if (q.size() < MAX_SIZE)
        {
            q.push(data);
		}
		cout << "Timestamp: " << sc_time_stamp() << "  Buffer: Writing data " << data << endl;
		
    }

    int read()
    {
        if (q.size() == MAX_SIZE)
        {
            int d = q.front();
            q.pop();
            not_full.notify(); // Notify the producer that space is available for writing
            cout << "Timestamp: " << sc_time_stamp() << "  Buffer: Reading data " << d << endl;
			return d;
        }
        else if(q.size() != MAX_SIZE)
        {
            int d = q.front();
            q.pop();
            cout << "Timestamp: " << sc_time_stamp() << "  Buffer: Reading data " << d << endl;
			return d;
		}
		
    }

    int empty()
    {
        return q.empty();
	}

	int size()
    {
        return q.size();
	}

    sc_event* data_available()
    {
        return &not_empty;
	}

    sc_event* space_available()
    {
        return &not_full;
    }

    int capacity()
    {
        return MAX_SIZE;
	}


    SC_CTOR(Buffer)
    {
        fifo_export.bind(*this);


    }


};






#endif // !BUFFER_H
