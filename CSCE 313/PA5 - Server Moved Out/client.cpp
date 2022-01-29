#include "common.h"
#include "BoundedBuffer.h"
#include "Histogram.h"
#include "common.h"
#include "HistogramCollection.h"
#include "TCPRequestChannel.h"
#include <thread>
#include <string>

using namespace std;

struct Response
{
    int person;
    double ecg;
};

void worker_thread_function(TCPRequestChannel* chan, BoundedBuffer* request_buffer, BoundedBuffer* responseBuffer, int mb)
{
   char buf[1024];
   char recvbuf[mb];
   while(true)
   {
        request_buffer->pop(buf,1024);
        MESSAGE_TYPE* m = (MESSAGE_TYPE*)buf;
        if(*m == DATA_MSG)
        {
            datamsg* d = (datamsg*) buf;
            chan->cwrite(d, sizeof(datamsg));
            double ecgval;
            chan->cread(&ecgval, sizeof(double));
            Response r{d->person,ecgval};
            responseBuffer->push((char*)&r, sizeof(r));
        }
      
        else if(*m == FILE_MSG)
        {
            filemsg* fm = (filemsg*)buf;
            string fname = (char*)(fm + 1);
            int s = sizeof(filemsg) + fname.size() + 1;
            chan->cwrite(buf,s);
            chan->cread(recvbuf,mb);
            string recvfname = "received/" + fname;
            FILE* fp = fopen(recvfname.c_str(),"r+");
            fseek(fp, fm->offset, SEEK_SET);
            fwrite(recvbuf, 1, fm->length, fp);
            fclose(fp);
        }

        else if(*m == QUIT_MSG)
        {
            chan->cwrite(m, sizeof(MESSAGE_TYPE));
            delete chan;
            return;
        }
   }
}

void patient_thread_function(int n, int p_no, BoundedBuffer* request_buffer)
{ 
   datamsg d (p_no, 0.0,1);
   for(int i = 0; i < n; i++)
   {
       request_buffer->push((char*)&d, sizeof(datamsg));
       d.seconds += 0.004;
   }
}

void histogram_thread_function (BoundedBuffer* responseBuffer, int p, HistogramCollection* hc)
{
    char buf[1024];
    while(true)
    {
        responseBuffer->pop(buf, 1024);
        Response* r =(Response*)buf;
        if(r->person == -1)
        {
            break;
        }

        hc->update(r->person, r->ecg);
    }
}

void file_thread_function(string fname, BoundedBuffer* request_buffer, string port, string host, int mb)
{
    TCPRequestChannel * chan = new TCPRequestChannel(host, port);
    string recvfname = "received/" + fname;
    char buf[1024];
    filemsg f (0,0);

    memcpy(buf, &f, sizeof(f));
    strcpy(buf + sizeof(f), fname.c_str());

    chan->cwrite(buf, sizeof(f) + fname.size() + 1);

    __int64_t filelength;
    chan->cread(&filelength, sizeof(filelength));
    FILE* fp = fopen(recvfname.c_str(), "w");

    fseek(fp, filelength,SEEK_SET);
    fclose(fp);

    filemsg* fm = (filemsg*)buf;
    __int64_t len = filelength;

    while(len > 0)
    {
        fm->length = min(len, (__int64_t) mb);
        request_buffer->push(buf,sizeof(filemsg) + fname.size() + 1);
        fm->offset += fm->length;
        len -= fm->length;
    }

    delete chan;
}

int main(int argc, char *argv[])
{
    int opt;
    int n = 15000;          // default number of requests per "patient"
    int p = 15;             // number of patients [1,15]
    int w = 100;            // default number of worker threads
    int b = 1024;       	// default capacity of the request buffer
	int m = MAX_MESSAGE; 	// default capacity of the message buffer
    string fname = "";      // default file name
    int h = 10;             // default histogram threads
    srand(time_t(NULL));
    bool fileReq = false;   // bool to determine if file is requested
    string port, host;      // determine hostname and port number

    while((opt = getopt(argc,argv, "m:n:b:w:p:f:h:a:r:")) != -1)
    {
        switch (opt)
        {
            case 'm':
                m = atoi (optarg);
                break;
            case 'n':
                n = atoi (optarg);
                break;
            case 'p':
                p = atoi (optarg);
                break;
            case 'b':
                b = atoi (optarg);
                break;
            case 'w':
                w = atoi (optarg);
                break;
            case 'f':
                fname = optarg;
                fileReq = true;
                break;
            case 'h':
                h = atoi (optarg);
                break;
            case 'a':
                host = optarg;
                break;
            case 'r':
                port = optarg;
                break;
        }
    }

    BoundedBuffer request_buffer(b);
    BoundedBuffer responseBuffer(b);
	HistogramCollection hc;
    
    for(int i = 0; i < p; i++)
    {
        Histogram* h = new Histogram(10, -2.0, 2.0);
        hc.add(h);
    }
    
    TCPRequestChannel* workerChannels[w];
    for(int i = 0; i < w; i++)
        workerChannels[i] = new TCPRequestChannel(host, port);
	
    thread workers[w];
    thread patients[p];
    thread histogram[h];
 
    struct timeval start, end;
    gettimeofday (&start, 0);
    MESSAGE_TYPE q = QUIT_MSG;

    if(fileReq)
    {
        thread filethread(file_thread_function, fname, &request_buffer, port, host, m);
        for(int i = 0; i < w; i++)
            workers[i] = thread(worker_thread_function, workerChannels[i], &request_buffer, &responseBuffer, m);

        filethread.join();
        for(int i = 0; i < w; i++)
        {
            MESSAGE_TYPE q = QUIT_MSG;
            request_buffer.push((char*)&q, sizeof(MESSAGE_TYPE));
        }

        for(int i = 0; i < w; i++)
            workers[i].join();

        gettimeofday(&end, 0);
    }
    else
    {
        for(int i = 0; i < p; i++)
            patients[i] = thread(patient_thread_function, n, i + 1, &request_buffer);
        
        for(int i = 0; i < h; i++)
            histogram[i] = thread(histogram_thread_function, &responseBuffer, p, &hc);
       
        for(int i = 0; i < w; i++)
            workers[i] = thread(worker_thread_function, workerChannels[i], &request_buffer, &responseBuffer, m); 
        
        cout << "Threads created." << endl;

        for(int i = 0; i < p; i++)
            patients[i].join();

        for(int i = 0; i < w; i++)
        {
            MESSAGE_TYPE q = QUIT_MSG;
            request_buffer.push((char*)&q,sizeof(MESSAGE_TYPE));
        }

        for(int i = 0; i < w; i++)
            workers[i].join();
   
        Response r {-1,0}; 
        
        for(int i = 0; i < h; i++)
            responseBuffer.push((char*)&r,sizeof(r));
        
        for(int i = 0; i < h; i++)
            histogram[i].join();

        cout << "Threads joined." << endl;
        
        gettimeofday(&end,0);
        hc.print();
    }

    int secs = (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec) / (int) 1e6;
    int usecs = (int)(end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec) % ((int) 1e6);
    cout << "Took " << secs << " seconds and " << usecs << " micro seconds" << endl;

    wait(0);
    cout << "Client terminated." << endl;
    
    return 0;
}





