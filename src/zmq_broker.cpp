//
//  Simple request-reply broker in C++
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>
// Broker shamelessly copied from ^
#include "zhelpers.hpp"
#include "zmq_testing.hpp"
#include <zmq.hpp>
int main (int argc, char *argv[])
{
    //  Prepare our context and sockets
    zmq::context_t context(1);
    zmq::socket_t frontend (context, ZMQ_ROUTER);
    zmq::socket_t backend (context, ZMQ_DEALER);

	frontend.bind(REQ_PROXY);
    backend.bind(RESP_PROXY);

    //  Initialize poll set
    zmq::pollitem_t items [] = {{ static_cast<void *>(frontend), 0, ZMQ_POLLIN, 0 },{ static_cast<void *>(backend),  0, ZMQ_POLLIN, 0 }};
	// std::vector<zmq::pollitem_t> items = {
	// 	{static_cast<void *>(frontend), 0, ZMQ_POLLIN, 0},
	// 	{static_cast<void *>(backend), 0, ZMQ_POLLIN, 0}
	// };
    //  Switch messages between sockets
    while (1) {
        zmq::message_t message;
        int more;               //  Multipart detection

        zmq::poll (&items [0], 2, -1);

        if (items [0].revents & ZMQ_POLLIN) {
            while (1) {
                //  Process all parts of the message
                frontend.recv(&message);
                size_t more_size = sizeof (more);
                frontend.getsockopt(ZMQ_RCVMORE, &more, &more_size);
                backend.send(message, more? ZMQ_SNDMORE: 0);

                if (!more)
                    break;      //  Last message part
            }
        }
        if (items [1].revents & ZMQ_POLLIN) {
            while (1) {
                //  Process all parts of the message
                backend.recv(&message);
                size_t more_size = sizeof (more);
                backend.getsockopt(ZMQ_RCVMORE, &more, &more_size);
                frontend.send(message, more? ZMQ_SNDMORE: 0);
                if (!more)
                    break;      //  Last message part
            }
        }
    }
    return 0;
}
