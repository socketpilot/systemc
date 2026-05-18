#include "producer.h"
#include <cstdlib>

Producer::Producer(sc_core::sc_module_name name)
    : sc_module(name),
    fifo_port("fifo_port"),
    current_data(0)
{
    std::cout
        << "Producer module is created."
        << std::endl;

    SC_THREAD(produce);
}


void Producer::produce()
{
    while (true)
    {
        // Check if buffer is full
        if (fifo_port->size() >= fifo_port->capacity())
        {
            wait(*(fifo_port->space_available()));

            std::cout
                << "Timestamp: "
                << sc_time_stamp()
                << " Producer: Buffer full, waiting for space"
                << std::endl;
        }

        // If Producer wakes, execution resumes here
        if (fifo_port->size() < fifo_port->capacity())
        {
            current_data = rand();

            fifo_port->write(current_data);

            std::cout
                << "Timestamp: "
                << sc_time_stamp()
                << " Producer: Producing data "
                << current_data
                << std::endl;
        }

        wait(10, SC_NS);
    }
}