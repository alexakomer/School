# makefile

all: server client

common.o: common.h common.cpp
	g++ -g -w -std=c++11 -c common.cpp

FIFOreqchannel.o: RequestChannel.h FIFOreqchannel.h FIFOreqchannel.cpp
	g++ -g -w -std=c++11 -c FIFOreqchannel.cpp

MQreqchannel.o: RequestChannel.h MQreqchannel.h MQreqchannel.cpp
	g++ -g -w -std=c++11 -c MQreqchannel.cpp

SHMreqchannel.o: RequestChannel.h SHMreqchannel.h SHMreqchannel.cpp
	g++ -g -w -std=c++11 -c SHMreqchannel.cpp

client: client.cpp MQreqchannel.o SHMreqchannel.o FIFOreqchannel.o common.o
	g++ -g -w -std=c++11 -o client client.cpp MQreqchannel.o SHMreqchannel.o FIFOreqchannel.o common.o -lpthread -lrt

server: server.cpp  MQreqchannel.o SHMreqchannel.o FIFOreqchannel.o common.o
	g++ -g -w -std=c++11 -o server server.cpp MQreqchannel.o SHMreqchannel.o FIFOreqchannel.o common.o -lpthread -lrt

clean:
	rm -rf *.o *.csv fifo* server client data*_*
