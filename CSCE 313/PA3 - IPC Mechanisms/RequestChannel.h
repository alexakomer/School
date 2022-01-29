#ifndef _RequestChannel_h_
#define _RequestChannel_h_

#include "common.h"

class RequestChannel 
{
    public:
        typedef enum {SERVER_SIDE, CLIENT_SIDE} Side;
        typedef enum {READ_MODE, WRITE_MODE} Mode;


    protected:
        string my_name;
        Side my_side;
        
        int wfd;
        int rfd;
        
        string p1, p2;
        virtual int open_ipc (string _pipe_name, int mode){;}


    public:
        /* CONSTRUCTOR/DESTRUCTOR */
        RequestChannel(const string _name, const Side _side):my_name(_name), my_side(_side){}        
        virtual ~RequestChannel(){};
        /* destruct operation should be derived class-specific */

        virtual int cread (void* msgbuf, int bufcapacity) = 0;
        /* Blocking read; returns the number of bytes read.
        If the read fails, it returns -1. */

        virtual int cwrite (void* msgbuf, int bufcapacity) = 0;
        /* Write the data to the channel. The function returns
        the number of characters written, or -1 when it fails */

        string name()
        {
            return my_name;
        }
};

#endif