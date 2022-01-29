
#ifndef _MQreqchannel_H_
#define _MQreqchannel_H_

#include "RequestChannel.h"
#include "common.h"


// This class parallels the FIFOreqchannel because only the bodies of functions
// are different, but function usage overlaps entirely 

class MQRequestChannel:public RequestChannel
{
	
public:
	MQRequestChannel(const string _name, const Side _side);
	~MQRequestChannel();

	int cread (void* msgbuf, int bufcapacity);
	int cwrite (void *msgbuf , int msglen);

	int open_ipc(string name, int mode);

};

#endif
