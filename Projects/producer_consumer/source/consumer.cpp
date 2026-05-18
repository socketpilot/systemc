#include "consumer.h"

consumer::consumer(sc_core::sc_module_name name)
    : sc_module(name),
    fifo_port("fifo_port")
{
    std::cout << "Consumer module is created." << std::endl;

    SC_THREAD(consume);
}

void consumer::consume()
{
    while (true)
    {
        if (fifo_port->empty())
        {
            std::cout
                << "Timestamp: "
                << sc_time_stamp()
                << " Consumer: Buffer empty, waiting..."
                << std::endl;

            wait(*(fifo_port->data_available()));
        }

        if (!fifo_port->empty())
        {
            int value = fifo_port->read();

            std::cout
                << "Timestamp: "
                << sc_time_stamp()
                << " Consumer: Consuming data "
                << value
                << std::endl;

            wait(15, SC_NS);
        }
    }
}