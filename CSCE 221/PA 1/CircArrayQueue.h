#include<iostream>
using namespace std;

class CircArrayQueue
{

private:
    int back, front; // initialize front and back
    int numElements; // length of array
    int capacity; // capacity of queue
    int *arr; // memory allocation of queue

    void resize(); // deep copy array and double capacity

public:
    CircArrayQueue(); // default constructor
    ~CircArrayQueue(); // destructor

    void display(); // print array values

    void enqueue(int value); // add element to end of queue
    int dequeue(); // return first value of queue and remove it
    int peek(); // return first element of queue
    int size(); // return length of queue
};
