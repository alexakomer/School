#include "common.h"
#include "mqueue.h"
#include "MQreqchannel.h"
using namespace std;

int buffercap = 256;

MQRequestChannel::MQRequestChannel(const string _name, const Side _side) : RequestChannel(_name, _side){
    p1 = "/mq_" + my_name + "1";
    p2 = "/mq_" + my_name + "2";
		
	if (_side == SERVER_SIDE)
    {
		wfd = open_ipc(p1, O_RDWR|O_CREAT);
		rfd = open_ipc(p2, O_RDWR|O_CREAT);
	}
	else
    {
		rfd = open_ipc(p1, O_RDWR|O_CREAT);
		wfd = open_ipc(p2, O_RDWR|O_CREAT);
 
	}
}

MQRequestChannel::~MQRequestChannel(){ 
    // different functions from standard fifo ones (mq_close, mq_unlnk)
	mq_close(wfd);
	mq_close(rfd);

	mq_unlink(p1.c_str());
	mq_unlink(p2.c_str());
}

int MQRequestChannel::open_ipc(string _pipe_name, int mode){
    // different functions from standard fifo ones (mq_open)
	struct mq_attr tempstruct {0, 1, buffercap, 0};
	int fd =(int) mq_open(_pipe_name.c_str(), mode, 0600, &tempstruct);

	if (fd < 0){
		EXITONERROR(_pipe_name);
	}
	return fd;
}

int MQRequestChannel::cread(void* msgbuf, int bufcapacity){
	// different functions from standard fifo ones (mq_receive)
    return mq_receive (rfd, (char*) msgbuf, 8192, 0); 
}

int MQRequestChannel::cwrite(void* msgbuf, int len){
    // different functions from standard fifo ones (mq_send)
	return mq_send (wfd, (char*) msgbuf, len, 0);
}

