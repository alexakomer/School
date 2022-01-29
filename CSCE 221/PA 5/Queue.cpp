#include<iostream>
#include "Queue.h"
using namespace std;

// default constructor
Queue::Queue() : head(-1), back(-1), capacity(10), numElements(0)
{
   arr = new int[capacity]{0};
}

// destructor
Queue::~Queue()
{
  delete arr;
}

// add element to end of queue
void Queue::push(int value)
{
    if ((head == 0 && back == capacity - 1) || (back == (head - 1) % (capacity - 1)))
    {
        resize();
    }
    else if (head == -1)
    {
        head = back = 0;
        arr[back] = value;
    }
    else if (back == capacity - 1 && head != 0)
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

int Queue::front()
{
  return arr[0];
}

bool Queue::empty()
{
  if (!numElements)
    return true;
  else
    return false;
}

// return first value of queue and remove it
int Queue::pop()
{
    if (head == -1)
    {
        cout << "Queue is Empty" << endl;
        return 0;
    }

    int val = arr[head];
    arr[head] = -1;
    if (head == back)
    {
        head = -1;
        back = -1;
    }
    else if (head == capacity - 1)
        head = 0;
    else
        head++;

    numElements--;
    return val;
}

// return first element of queue
int Queue::peek()
{
    if (size() == 0)
      return -1;
    return arr[head];
}

// return length of queue
int Queue::size()
{
    return numElements;
}

// deep copy array and double capacity
void Queue::resize()
{
    capacity *= 2;
    int idx = 0;
    int* tempQueue = new int[capacity]{0};
    for (int i = head; i < numElements; i++)
    {
      tempQueue[idx] = arr[i];
      idx++;
    }

    for (int i = 0; i < head; i++)
    {
      tempQueue[idx] = arr[i];
      idx++;
    }
    delete arr;
    head = 0;
    back = numElements - 1;
    arr = tempQueue;
}

// print array values
void Queue::display()
{
    if (head == -1)
    {
        cout << "Queue is Empty" << endl;
        return;
    }
    // cout << "Elements in Circular Queue are: " << endl;
    if (back >= head)
    {
        for (int i = head; i <= back; i++)
            cout << arr[i] << " ";
    }
    else
    {
        for (int i = head; i < capacity; i++)
            cout << arr[i] << " ";

        for (int i = 0; i <= back; i++)
            cout << arr[i] << " ";
    }
    cout << endl;
}
