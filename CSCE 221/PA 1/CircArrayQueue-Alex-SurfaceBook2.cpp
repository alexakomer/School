#include<iostream>
#include "CircArrayQueue.h"
using namespace std;

// default constructor
CircArrayQueue::CircArrayQueue() : front(-1), back(-1), capacity(10), numElements(0)
{
   arr = new int[capacity]{0};
}

// destructor
CircArrayQueue::~CircArrayQueue()
{
  delete arr;
}

// add element to end of queue
void CircArrayQueue::enqueue(int value)
{
    if ((front == 0 && back == capacity - 1) || (back == (front - 1) % (capacity - 1)))
    {
        resize();
    }
    else if (front == -1)
    {
        front = back = 0;
        arr[back] = value;
    }
    else if (back == capacity - 1 && front != 0)
    {
        back = 0;
        arr[back] = value;
    }
    else
    {
        back++;
        arr[back] = value;
    }
    numElements++;
}

// return first value of queue and remove it
int CircArrayQueue::dequeue()
{
    if (front == -1)
    {
        cout << "Queue is Empty" << endl;
        return 0;
    }

    int val = arr[front];
    arr[front] = -1;
    if (front == back)
    {
        front = -1;
        back = -1;
    }
    else if (front == capacity - 1)
        front = 0;
    else
        front++;

    numElements--;
    return val;
}

// return first element of queue
int CircArrayQueue::peek()
{
    if (size() == 0)
      return -1;
    return arr[front];
}

// return length of queue
int CircArrayQueue::size()
{
    return numElements;
}

// deep copy array and double capacity
void CircArrayQueue::resize()
{
    capacity *= 2;
    int idx = 0;
    int* tempQueue = new int[capacity]{0};
    for (int i = front; i < numElements; i++)
    {
      tempQueue[idx] = arr[i];
      idx++;
    }

    for (int i = 0; i < front; i++)
    {
      tempQueue[idx] = arr[i];
      idx++;
    }
    delete arr;
    front = 0;
    back = numElements - 1;
    arr = tempQueue;
}

// print array values
void CircArrayQueue::display()
{
    if (front == -1)
    {
        cout << "Queue is Empty" << endl;
        return;
    }
    // cout << "Elements in Circular CircArrayQueue are: " << endl;
    if (back >= front)
    {
        for (int i = front; i <= back; i++)
            cout << arr[i] << " ";
    }
    else
    {
        for (int i = front; i < capacity; i++)
            cout << arr[i] << " ";

        for (int i = 0; i <= back; i++)
            cout << arr[i] << " ";
    }
    cout << endl;
}
