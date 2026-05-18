#include <systemc.h>
#include "producer.h"
#include "consumer.h"
#include "buffer.h"

int sc_main(int argc, char* argv[])
{

	Producer producer("Producer");
	consumer consumer("Consumer");
	Buffer buffer("Buffer");
	producer.fifo_port(buffer.fifo_export);
	consumer.fifo_port(buffer.fifo_export);
	sc_start(500,SC_NS); // Run the simulation for 500 nanoseconds
	return 0;
}


