CC=g++
CFLAGS= -std=c++11 -O3 -Wall -Wunused $(INC)
INC= -I../inc/ -I../cfg/
DEPS= -lzmq

OBJS= zmq_sub zmq_pub

all: clean $(OBJECT) $(EXECUTABLE)
	$(CC) $(CFLAGS) ../src/zmq_broker.cpp -o zmq_broker $(DEPS)
	$(CC) $(CFLAGS) ../src/zmq_client.cpp -o zmq_client $(DEPS)
	$(CC) $(CFLAGS) ../src/zmq_worker.cpp -o zmq_worker $(DEPS)
	$(CC) $(CFLAGS) ../src/tests.cpp -o tests $(DEPS)
	@chmod +x *
clean:
	-rm -f zmq_*
