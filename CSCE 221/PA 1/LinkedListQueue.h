#include <iostream>
using namespace std;

struct Node
{
    Node* next;
    Node* prev;
    int data;

    Node(); // default constructor
    Node(int val); // constructor
};

class LinkedListQueue
{
    private:
        Node* head;
        Node* tail;
        size_t len;

    public:
        LinkedListQueue(); // default constructor
        ~LinkedListQueue(); // destructor

        void display(); // print linked list values

        void enqueue(int value); // add element to end of queue
        int dequeue(); // return first value of queue and remove it
        int peek(); // return first element of queue
        int size(); // return length of queue
};
