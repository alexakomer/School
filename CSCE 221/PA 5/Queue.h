#include<iostream>
using namespace std;

class Queue
{

private:
    int back, head; // initialize front and back
    int numElements; // length of array
    int capacity; // capacity of queue
    int *arr; // memory allocation of queue

    void resize(); // deep copy array and double capacity

public:
    Queue(); // default constructor
    ~Queue(); // destructor

    void display(); // print array values

    bool empty();

    int front();

    void push(int value); // add element to end of queue
    int pop(); // return first value of queue and remove it
    int peek(); // return first element of queue
    int size(); // return length of queue
};
