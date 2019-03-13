#include "zmq_testing.hpp"
#include <iostream>
#include <zmq.hpp>
#include <unistd.h>
#include <string>
int main(int argc, char** argv)
{
	zmq::context_t context(1);
	zmq::socket_t requester(context, ZMQ_REQ);
	requester.connect(REQ_PROXY);

	for(int req = 0; req < 10; req++)
	{
		std::cout << "Sending stuff" << std::endl;
		s_send(requester, "Hello");
		std::string str = s_recv(requester);
		std::cout << "Received reply " << req << " [" << str << "] " << std::endl;
	}
	return 0;
}
