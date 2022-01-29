#ifndef _SHMreqchannel_H_
#define _SHMreqchannel_H_
#include "RequestChannel.h"
#include "common.h"

#include <semaphore.h>
#include <sys/mman.h>
#include <string>

using namespace std;

class SHMQueue // necessary to create SHM IPC objects
{
private:
    char* shmBuffer;
    sem_t* sendDone;
    sem_t* readDone;
    int len;
    string name;

public:
    SHMQueue(string _name, int _len): name(_name), len(_len)
    {
        int fd = shm_open(name.c_str(), O_RDWR|O_CREAT, 0600);
        if (fd < 0)
            EXITONERROR("Could not create or open SHM");

        //set the length to 1024, because the default would have been 0
        ftruncate(fd,len); 

        shmBuffer = (char*) mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
       
        if (!shmBuffer)
            EXITONERROR("Could not map");

        // setting readDone to 1 allows the program to start
        // otherwise, neither will ever operate
        readDone = sem_open((name + "_readDone").c_str(), O_CREAT, 0600, 1); 
        sendDone = sem_open((name + "_sendDone").c_str(), O_CREAT,0600,0); 
    }

    ~SHMQueue()
    {
        sem_close(sendDone);
        sem_close(readDone);
        sem_unlink((name + "_readDone").c_str());
        sem_unlink((name + "_sendDone").c_str());

        munmap(shmBuffer, len);
        shm_unlink(name.c_str());
    }

    int shm_rec(void* msgbuf, int bufcapacity)
    {
        sem_wait(sendDone); // have semaphore wait for reader to finish
        memcpy(msgbuf, shmBuffer, bufcapacity);
        sem_post(readDone);

        return bufcapacity;
    }

    int shm_send(void* msgbuf, int len)
    {
        sem_wait(readDone); // have semaphore wait for writer to finish
        memcpy(shmBuffer, msgbuf, len);
        sem_post(sendDone);
        
        return len;
    }
};

class SHMRequestChannel:public RequestChannel
{
private:
    SHMQueue * shmq1;
    SHMQueue * shmq2;
    int len;
public:
    SHMRequestChannel(const string _name, const Side _side, int _len);
    ~SHMRequestChannel();

    int cread(void* msgbuf, int bufcapacity);
    int cwrite(void *msgbuf , int msglen);
};

#endif