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
#include "MQreqchannel.h"
#include "SHMreqchannel.h"
#include <iostream>
#include <sys/wait.h>
#include <bits/stdc++.h>
#include <chrono>
#include <vector>

using namespace std;


int main(int argc, char *argv[])
{
	int opt;
	int p = 1;
	double t = 0.0;
	int e = 1;
	bool thousandPoints = true;
	int msgLimit = MAX_MESSAGE;
	bool channelCreate = false;
	int numChannels = 1;
	bool fileCreate = false;
	bool data = false;
	string ipcType = "f";
	
	string fname = "";

	while ((opt = getopt(argc, argv, "p:t:e:f:m:c:i:")) != -1) {
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
				thousandPoints = false;
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
				numChannels = atoi(optarg);
				channelCreate = true;
				break;
			case 'i':
				ipcType = optarg;
				break;
		}
	}

	int pid = fork();
	int status;
	if(!pid) // this controls the child process, or the server
	{
		char * args [] = {"./server", "-m", (char*) to_string(msgLimit).c_str(), "-i", (char*) ipcType.c_str(), NULL};
		if (execvp(args[0], args) < 0)
		{
			perror("The execvp has been processed.");
			exit(0);
		}
	}


	chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

	RequestChannel* control_chan;
	if (ipcType == "q")
		control_chan = new MQRequestChannel("control", RequestChannel::CLIENT_SIDE);
	else if (ipcType == "s")
		control_chan = new SHMRequestChannel("control", RequestChannel::CLIENT_SIDE, msgLimit);
	else
		control_chan = new FIFORequestChannel("control", RequestChannel::CLIENT_SIDE);

	vector<RequestChannel*> channels;
	channels.push_back(control_chan);

	if (channelCreate)
	{
		for (int i = 0; i < numChannels; i++)
		{

			MESSAGE_TYPE ch = NEWCHANNEL_MSG;
			control_chan->cwrite(&ch, sizeof(MESSAGE_TYPE));

			char* chan_name = new char[30];
			control_chan->cread (chan_name, 30);


			RequestChannel* newChan;

			if (ipcType == "q")
				newChan = new MQRequestChannel(chan_name, RequestChannel::CLIENT_SIDE);
			else if (ipcType == "s")
				newChan = new SHMRequestChannel(chan_name, RequestChannel::CLIENT_SIDE, msgLimit);
			else
				newChan = new FIFORequestChannel(chan_name, RequestChannel::CLIENT_SIDE);


			cout << "New channel by the name " << chan_name << " is created" << endl;
			channels.push_back(newChan);
		}
	}

	
	if (data)
	{
		ofstream data_points;
		if (thousandPoints)
		{
			string patient_file = "x" + to_string(p) + ".csv";
			data_points.open(patient_file);
		}
	
		for (int k = 0; k < channels.size(); k++)
		{
			if (thousandPoints)
			{
				for (double i = t; i < t + 4; i+= 0.004)
				{
					datamsg x (p, i, 1);
					datamsg y (p, i, 2);

					data_points << i << ",";

					channels[k]->cwrite (&x, sizeof (datamsg)); // question
					double reply;
					int nbytes = channels[k]->cread (&reply, sizeof(double)); //answer

					data_points << reply << ",";

					channels[k]->cwrite (&y, sizeof (datamsg)); // question
					double reply2;
					int nbytes2 = channels[k]->cread (&reply2, sizeof(double)); //answer

					data_points << reply2 << endl;
				}
			}
			else
			{
				datamsg x (p, t, e); // request data points
				channels[k]->cwrite (&x, sizeof (datamsg)); // question

				double reply;
				
				channels[k]->cread (&reply, sizeof(double)); //answer

				cout << reply << endl;

			}

		}

		if (thousandPoints)
			data_points.close();
	}

	if (fileCreate)
	{
		filemsg fm (0,0); //get filesize
		
		int len = sizeof (filemsg) + fname.size()+1;
		char* buf2 = new char[len];
		memcpy (buf2, &fm, sizeof (filemsg));
		strcpy (buf2 + sizeof (filemsg), fname.c_str());
		control_chan->cwrite (buf2, len);  // I want the file length;
		
		__int64_t fileSize;
		control_chan->cread(&fileSize, sizeof(__int64_t));

        filemsg *f = (filemsg *) buf2;

		string path = string("received/") + fname;
		FILE *oFile = fopen(path.c_str(), "wb");

		char* endBuffer = new char[MAX_MESSAGE]; // buffer to write everything into

		for (int j = 0; j < channels.size(); j++)
		{
			__int64_t remainder = fileSize / channels.size();

			while(remainder > 0)
			{
				f->length = (int) min(remainder, (__int64_t) MAX_MESSAGE);
                channels.at(j)->cwrite(buf2, len);
                channels.at(j)->cread(endBuffer, MAX_MESSAGE);
                fwrite(endBuffer, 1, f->length, oFile);
                remainder -= f->length;
                f->offset += f->length;
			}
		}

		fclose(oFile);
		delete endBuffer;
		delete buf2;
		cout << "File transfer completed" << endl;
	}

	// close all channels created
	for (int i = 0; i < channels.size(); i++)
	{
		MESSAGE_TYPE m2 = QUIT_MSG;
		channels[i]->cwrite (&m2, sizeof (MESSAGE_TYPE));
	}

	chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
	cout << "Elapsed: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " ms" <<  endl;


	waitpid(pid, &status, 0); // here to ensure the server dies
	exit(1);
}
