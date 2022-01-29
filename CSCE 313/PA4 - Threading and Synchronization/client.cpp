#include "common.h"
#include "BoundedBuffer.h"
#include "Histogram.h"
#include "common.h"
#include "HistogramCollection.h"
#include "FIFOreqchannel.h"
#include <thread>

using namespace std;

FIFORequestChannel* create_new_channel (FIFORequestChannel* mainchan){
    char name[1024];
    MESSAGE_TYPE  m = NEWCHANNEL_MSG;
    mainchan -> cwrite (&m, sizeof(m));
    mainchan -> cread (name, 1024);
    FIFORequestChannel* newchan = new FIFORequestChannel (name, FIFORequestChannel::CLIENT_SIDE);
    return newchan;
}

struct Response
{
    int person;
    double ecg;
};

void patient_thread_function(int n,int patientNum,BoundedBuffer* requestBuf)
{
    datamsg d (patientNum, 0.0, 1);
    for(int i = 0; i < n; i++){
        requestBuf -> push ((char*) &d, sizeof(datamsg));
        d.seconds += 0.004;
    }
}

void file_thread_function(string fname, BoundedBuffer* request_buffer, FIFORequestChannel* chan, int mb){

    //create new file
    char buf[1024];
    filemsg f (0,0);
    memcpy (buf, &f, sizeof(f));
    strcpy (buf + sizeof(f), fname.c_str());
    chan->cwrite (buf, sizeof (f) + fname.size() + 1); // allocate same amount of space as original file
    __int64_t filelength;
    chan->cread(&filelength, sizeof(filelength));
    string recvfname = "received/" + fname;
    FILE* fp = fopen(recvfname.c_str(), "w");
    fseek (fp, filelength, SEEK_SET);
    fclose(fp);

    //generate corresponding file messages
    filemsg* fm = (filemsg*) buf;
    __int64_t remlen = filelength;
    while(remlen > 0)
	{
        fm->length = min(remlen, (__int64_t) mb);
        request_buffer->push(buf, sizeof(filemsg) + fname.size()+1);
        fm->offset += fm->length;
        remlen -= fm->length;
    }
    assert(remlen == 0);
}

void worker_thread_function (FIFORequestChannel* chan, BoundedBuffer* requestBuf, int mb, BoundedBuffer* responseBuf){
    char buf [1024];
    double resp = 0;
    char recvbuf[mb];

    while(true)
	{
        requestBuf->pop(buf, 1024);
        MESSAGE_TYPE* m = (MESSAGE_TYPE*) buf;

        if(*m == DATA_MSG)
		{
            datamsg* d = (datamsg*) buf;
            chan -> cwrite (buf, sizeof(datamsg));
            chan -> cread (&resp, sizeof(double));
            Response r{d -> person, resp};
            responseBuf->push((char*)&r, sizeof(r));
        }
		else if (*m == FILE_MSG)
		{
            filemsg* fm = (filemsg*) buf;
            string fname = (char*)(fm + 1);
            int sz = sizeof(filemsg) + fname.size() + 1;

            chan -> cwrite (buf, sz);
            chan -> cread (recvbuf, mb);

            string recvfname = "received/" + fname;
            FILE* fp = fopen(recvfname.c_str(), "r+");
            fseek (fp, fm->offset,SEEK_SET);
            fwrite (recvbuf, 1, fm->length, fp);
            fclose (fp);
        }
		else if(*m == QUIT_MSG)
		{
            chan -> cwrite (m, sizeof(MESSAGE_TYPE));
            delete chan;
            break;
        }
    }
}

void histogram_thread_function (BoundedBuffer* responseBuf, HistogramCollection* hc){
    char buf[1024];
    while(true)
	{
        responseBuf -> pop ((char*)&buf,1024);
        Response* resp = (Response*) buf;

        if(resp -> person == -1)
            break;

        hc->update (resp -> person, resp->ecg);
    }
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
    bool fileRequest = false; // bool to determine if file is requested

    while((opt = getopt(argc,argv, "m:n:b:w:p:f:h:")) != -1)
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
                fileRequest = true;
                break;
            case 'h':
                h = atoi (optarg);
                break;
        }
    }

 	int pid = fork();
	int status;
	if(!pid) // this controls the child process, or the server
	{
		char * args [] = {"./server", "-m", (char*) to_string(m).c_str(), NULL};
		if (execvp(args[0], args) < 0)
		{
			perror("The execvp has been processed.");
			exit(0);
		}
	}
    struct timeval start, end;
    gettimeofday (&start, 0);

    if(fileRequest)
    {

	    FIFORequestChannel* chan = new FIFORequestChannel("control", FIFORequestChannel::CLIENT_SIDE);
        BoundedBuffer request_buffer(b);
        BoundedBuffer responseBuffer(b);
	    HistogramCollection hc;
        thread workers [w];

        FIFORequestChannel* wchans[w];
        for(int i = 0; i < w; i++)
        {
            MESSAGE_TYPE m = NEWCHANNEL_MSG;
            chan->cwrite(&m, sizeof(m));
            char name[1024];
            chan->cread(name, 1024);
            FIFORequestChannel* newchan = new FIFORequestChannel(name, FIFORequestChannel::CLIENT_SIDE);
            wchans[i] = newchan;
        }

        /* Start all threads here */
        thread filethread(file_thread_function ,fname, &request_buffer, chan, m);

        for(int i = 0; i < w; i++)
           workers[i] = thread(worker_thread_function, wchans[i], &request_buffer, m, &responseBuffer);

        /* Join all threads here */
        filethread.join();

        MESSAGE_TYPE q = QUIT_MSG;
        for(int i = 0; i < w; i++)
            request_buffer.push((char*)&q, sizeof(MESSAGE_TYPE));
    
        for(int i = 0; i < w; i++)
           workers[i].join();

        Response r {-1,0};

        for(int i = 0; i < h; i++)
            responseBuffer.push((char*)&r,sizeof(r));

        gettimeofday (&end, 0);

        int secs = (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)/(int) 1e6;
        int usecs = (int)(end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)%((int) 1e6);
        cout << "Took " << secs << " seconds and " << usecs << " micro seconds" << endl;

        // MESSAGE_TYPE q = QUIT_MSG;
        chan->cwrite ((char *) &q, sizeof (MESSAGE_TYPE));
        cout << "Client terminated." << endl;
        wait(0);
        delete chan;
    }
    else
    {
	    FIFORequestChannel* chan = new FIFORequestChannel("control", FIFORequestChannel::CLIENT_SIDE);
        BoundedBuffer request_buffer(b);
        BoundedBuffer responseBuffer(b);
	    HistogramCollection hc;
        thread workers [w];
        thread patient [p];
        thread hists[h];

        FIFORequestChannel* wchans[w];
        for(int i = 0; i < w; i++){
            MESSAGE_TYPE m = NEWCHANNEL_MSG;
            chan->cwrite(&m, sizeof(m));
            char name[1024];
            chan->cread(name, 1024);
            FIFORequestChannel* newchan = new FIFORequestChannel(name, FIFORequestChannel::CLIENT_SIDE);
            wchans[i] = newchan;
        }

        /* Start all threads here */
        for(int i = 0;i < p; i++)
        {
            Histogram* h = new Histogram(10, -2.0, 2.0);
            hc.add(h);
        }

        for(int i = 0; i < p; i++)
            patient[i] = thread(patient_thread_function, n, i+1,&request_buffer);

        for(int i = 0; i < w; i++)
           workers[i] = thread(worker_thread_function, wchans[i], &request_buffer, m, &responseBuffer);

        for(int i = 0; i < h; i++)
           hists[i] = thread(histogram_thread_function, &responseBuffer, &hc);

        /* Join all threads here */
        for(int i = 0; i < p; i++)
           patient[i].join();

        MESSAGE_TYPE q = QUIT_MSG;
        for(int i = 0; i < w;i++)
            request_buffer.push((char*)&q, sizeof(MESSAGE_TYPE));

        for(int i = 0; i < w; i++)
           workers[i].join();

        Response r {-1,0};

        for(int i = 0; i < h; i++)
            responseBuffer.push((char*)&r, sizeof(r));

        for(int i = 0; i < h; i++)
            hists[i].join();

        gettimeofday (&end, 0);

	    hc.print();

        int secs = (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)/(int) 1e6;
        int usecs = (int)(end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)%((int) 1e6);
        cout << "Took " << secs << " seconds and " << usecs << " micro seconds" << endl;

        // MESSAGE_TYPE q = QUIT_MSG;
        chan->cwrite ((char *) &q, sizeof (MESSAGE_TYPE));
        cout << "Client terminated." << endl;
        wait(0);
        delete chan;
    }
}
