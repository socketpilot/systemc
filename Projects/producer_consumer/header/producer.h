#pragma once
#ifndef PRODUCER_H
#define PRODUCER_H

#include <systemc.h>
#include "interface.h"

class Producer : public sc_core::sc_module
{
public:

    sc_port<fifo_if> fifo_port;

    int current_data;

    // Constructor declaration
    Producer(sc_core::sc_module_name name);

    // Thread function declaration
    void produce();
};

#endif