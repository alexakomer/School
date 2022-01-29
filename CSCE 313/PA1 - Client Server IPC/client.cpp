/*
    Tanzir Ahmed
    Department of Computer Science & Engineering
    Texas A&M University
    Date  : 2/8/20
	Original author of the starter code
	
	Please include your name and UIN below
	Name: Alexander Akomer
	UIN: 928005535
 */
#include "common.h"
#include "FIFOreqchannel.h"
#include <iostream>
#include <sys/wait.h>
#include <chrono>

using namespace std;


int main(int argc, char *argv[]){


	int pid = fork();
	int status;
	if (pid) // this controls the parent process, or the client
	{

		chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

		FIFORequestChannel chan ("control", FIFORequestChannel::CLIENT_SIDE);
		
		int opt;
		int p = 1;
		double t = 0.0;
		int e = 1;
		int msgLimit = MAX_MESSAGE;
		bool channelCreate = false;
		bool fileCreate = false;
		bool data = false;
		
		string fname = "";
		while ((opt = getopt(argc, argv, "p:t:e:f:m:c")) != -1) {
			switch (opt) {
				case 'p':
					p = atoi (optarg);
					data = true;
					break;
				case 't':
					t = atof (optarg);
					data = true;
					break;
				case 'e':
					e = atoi (optarg);
					data = true;
					break;
				case 'f':
					fileCreate = true;
					fname = optarg;
					break;
				case 'm':
					msgLimit = atoi(optarg);
					cout << "Client buffer changed to " << msgLimit << endl;
					break;
				case 'c':
					channelCreate = true;
					break;
			}
		}

		
		if (data)
		{
			ofstream data_points;
			// string patient_file = "x" + to_string(p) + ".csv";
			// data_points.open(patient_file);
			data_points.open("x1.csv");

			for (double i = t; i < t + 4; i += 0.004)
			{
				// datamsg x (1, i, 1);
				// datamsg y (1, i, 2);

				datamsg x (p, i, 1);
				datamsg y (p, i, 2);

				data_points << i << ",";

				chan.cwrite (&x, sizeof (datamsg)); // question
				double reply;
				int nbytes = chan.cread (&reply, sizeof(double)); //answer

				data_points << reply << ",";

				chan.cwrite (&y, sizeof (datamsg)); // question
				double reply2;
				int nbytes2 = chan.cread (&reply2, sizeof(double)); //answer

				data_points << reply2 << endl;
			}

			data_points.close();
		}

		if (fileCreate)
		{
			filemsg fm (0,0);
			
			int len = sizeof (filemsg) + fname.size()+1;
			char* buf2 = new char[len];
			memcpy (buf2, &fm, sizeof (filemsg));
			strcpy (buf2 + sizeof (filemsg), fname.c_str());
			chan.cwrite (buf2, len);  // I want the file length;
			
			__int64_t fileSize;
			chan.cread(&fileSize, sizeof(__int64_t));

			int remainder = fileSize % msgLimit;

			string path = string("received/") + fname;
			FILE *oFile = fopen(path.c_str(), "wb");

			for (int i = 0; i < fileSize - remainder; i += msgLimit)
			{
				filemsg *chunk = (filemsg*) buf2; 
				chunk->length = msgLimit;
				chunk->offset = i;
				chan.cwrite(buf2, len);
				char* char_buf = new char[msgLimit];
				chan.cread(char_buf, msgLimit);
				fwrite(char_buf, 1, msgLimit, oFile);
			}

			if (remainder)
			{
				filemsg *chunk = (filemsg*) buf2; 
				chunk->length = remainder;
				chunk->offset = fileSize - remainder;
				chan.cwrite(buf2, len);
				char* char_buf = new char[remainder];
				chan.cread(char_buf, remainder);
				fwrite(char_buf, 1, remainder, oFile);
			}

			fclose(oFile);
		}
		
		if (channelCreate)
		{
			MESSAGE_TYPE ch = NEWCHANNEL_MSG;
			chan.cwrite(&ch, sizeof(MESSAGE_TYPE));
			char* chan_name = new char[30];
			chan.cread (chan_name, 30);
			// cout << chan_name << endl;

			FIFORequestChannel chan2 (chan_name, FIFORequestChannel::CLIENT_SIDE);

			datamsg x (1, 0, 1); // request data points
			chan2.cwrite (&x, sizeof (datamsg)); // question
			double reply;
			chan2.cread (&reply, sizeof(double)); //answer
			cout << reply << endl;

			datamsg y (1, 0.004, 1); // request data points
			chan2.cwrite (&y, sizeof (datamsg)); // question
			double reply2;
			chan2.cread (&reply2, sizeof(double)); //answer
			cout << reply2 << endl;

			datamsg z (1, 0.008, 1); // request data points
			chan2.cwrite (&z, sizeof (datamsg)); // question
			double reply3;
			chan2.cread (&reply3, sizeof(double)); //answer
			cout << reply3 << endl;

			MESSAGE_TYPE m2 = QUIT_MSG;
			chan2.cwrite (&m2, sizeof (MESSAGE_TYPE));
		}


		// closing the channel    
		MESSAGE_TYPE m = QUIT_MSG;
		chan.cwrite (&m, sizeof (MESSAGE_TYPE));

		chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
        // cout << "Elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl;
		cout << "Elapsed: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " ms" <<  endl;


		waitpid(pid, &status, 0); // here to ensure the server dies
		exit(1);
	}
	else // this controls the child process, or the server
	{

		int opt;
		int msgLimit = MAX_MESSAGE;
		// char * argM = "256";
		
		while ((opt = getopt(argc, argv, "p:t:e:f:m:c")) != -1) {
			char* buf_arg[] = {"./server", "-m", optarg, NULL};
			switch (opt) {

				case 'm':
					// argM = optarg;
					msgLimit = atoi(optarg);
					cout << "Client buffer changed to " << msgLimit << endl;
					execvp(buf_arg[0], buf_arg);
					break;
			}
		}
			execvp("./server", NULL);

	}



}
