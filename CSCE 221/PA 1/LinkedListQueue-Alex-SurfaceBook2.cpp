#include<iostream>
#include "LinkedListQueue.h"
using namespace std;

// default Node constructor
Node::Node() : next(nullptr), prev(nullptr), data(0) {}

// Node constructor
Node::Node(int val) : next(nullptr), prev(nullptr), data(val) {}

// default LinkedListQueue constructor
LinkedListQueue::LinkedListQueue() : head(nullptr), tail(nullptr), len(0) {}

// LinkedListQueue destructor
LinkedListQueue::~LinkedListQueue()
{
    Node* elem = head;
    while (elem != nullptr)
    {
        Node* next = elem -> next;
        delete elem;
        elem = next;
    }
    len = 0;
}

// add element to end of queue
void LinkedListQueue::enqueue(int x)
{
    Node* temp = new Node(x);

    if (tail == nullptr)
    {
        head = tail = temp;
    }
    else
    {
      tail -> next = temp;
      tail = temp;
    }
    len++;
}

// return first value of queue and remove it
int LinkedListQueue::dequeue()
{
    if (head == nullptr)
    {
      cout << "Queue is Empty" << endl;
      return 0;
    }

    int dequeuedData = head -> data;

    Node* temp = head;
    head = head -> next;

    if (head == nullptr)
        tail = nullptr;

    delete (temp);
    len--;
    return dequeuedData;
}

int LinkedListQueue::peek()
{
    if (head == nullptr)
      return -1;
    return head -> data;
}

int LinkedListQueue::size()
{
    return len;
}

void LinkedListQueue::display()
{
    Node* curr = head;
    while (curr != nullptr) {
        Node* next = curr -> next;
        cout << curr -> data << " ";
        curr = next;
    }
    cout << endl;
}
