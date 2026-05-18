#pragma once
#ifndef CONSUMER_H
#define CONSUMER_H

#include <systemc.h>
#include "interface.h"

class consumer : public sc_core::sc_module
{
public:

    sc_port<fifo_if> fifo_port;

    // Constructor declaration
    consumer(sc_core::sc_module_name name);

    // Thread function declaration
    void consume();
};

#endif