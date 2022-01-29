#ifndef BoundedBuffer_h
#define BoundedBuffer_h

#include <stdio.h>
#include <queue>
#include <string>
#include <pthread.h>
#include <mutex>
#include <condition_variable>
#include <assert.h>

using namespace std;

class BoundedBuffer
{
private:
	int cap; // max number of items in the buffer
	queue<vector<char>> q;	/* the queue of items in the buffer. Note
	that each item a sequence of characters that is best represented by a vector<char> for 2 reasons:
	1. An STL std::string cannot keep binary/non-printables
	2. The other alternative is keeping a char* for the sequence and an integer length (i.e., the items can be of variable length).
	While this would work, it is clearly more tedious */

	// add necessary synchronization variables and data structures 
	// for thread safety
	mutex m;
	condition_variable fullSlots; // for wait by the pop and signaled by push function
	condition_variable emptySlots; // waited on by the push and signaled by pop function
	int occupancy;

public:
	BoundedBuffer(int _cap):cap(_cap), occupancy(0)
	{

	}
	~BoundedBuffer()
	{

	}

	void push(char* data, int len)
	{
		
		unique_lock<mutex> l(m);
		emptySlots.wait(l, [this, len]{return (occupancy + len) < cap;});

		vector<char> d (data, data + len);

		q.push(d);
		occupancy += len;
		fullSlots.notify_one();
		l.unlock();
	}

	int pop(char* buf, int bufcap)
	{

		unique_lock<mutex> l(m);
		fullSlots.wait(l,[this]{return q.size() > 0;});

		vector<char> d = q.front();

		q.pop();
		int length = d.size();
		occupancy -= length;
		l.unlock();

		memcpy(buf, d.data(), d.size());
		emptySlots.notify_one();

		return d.size();
	}
};

#endif /* BoundedBuffer_ */
