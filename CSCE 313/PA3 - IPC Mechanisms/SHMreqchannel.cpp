#include "common.h"
#include "SHMreqchannel.h"
using namespace std;

SHMRequestChannel::SHMRequestChannel(const string _name, const Side _side, int _len) : RequestChannel(_name, _side)
{
    p1 = "/shm_" + my_name + "1";
    p2 = "/shm_" + my_name + "2";

    len = _len;

    shmq1 = new SHMQueue(p1, len);
    shmq2 = new SHMQueue(p2, len);
       
    if (my_side == CLIENT_SIDE) // same logic as before, simplified
        swap(shmq1, shmq2);
}

SHMRequestChannel::~SHMRequestChannel()
{ 
    // need only delete SHMQueues so that they call their implicit destructor
    delete shmq1;
    delete shmq2;
}

int SHMRequestChannel::cread(void* msgbuf, int bufcapacity)
{
	// use custom function shm_rec to account for semaphore control
    return shmq1 -> shm_rec(msgbuf, bufcapacity); 
}

int SHMRequestChannel::cwrite(void* msgbuf, int len)
{
	// use custom function shm_send to account for semaphore control
	return shmq2 -> shm_send(msgbuf, len);
}

