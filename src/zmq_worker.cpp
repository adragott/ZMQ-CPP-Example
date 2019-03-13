#include "zmq_testing.hpp"
#include <iostream>
#include <zmq.hpp>
#include <unistd.h>
#include <string>
int main(int argc, char** argv)
{
	zmq::context_t context(1);
	zmq::socket_t responder(context, ZMQ_REP);
	responder.connect(RESP_PROXY);
	for(;;)
	{
		std::string str = s_recv(responder);
		std::cout << "Received request: " << str << std::endl;
		s_send(responder, "World");
	}
	return 0;
}
