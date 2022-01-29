#include "CircArrayQueue.h"
#include "LinkedListQueue.h"
#include <iostream>
#include <chrono>
using namespace std;

int main()
{
    int iterations = 10000;
    string response;
    cout << "Select Queue Implementation - Type \"1\" for Linked List or \"2\" for Circular Array: ";
    cin >> response;

    if (response == "1")
    {
        LinkedListQueue ll;

        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
        for (int i = 1; i <= iterations; i++)
        {
            ll.enqueue(i);
        }
        chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
        cout << "Elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl;
    }

    else if (response == "2")
    {
        CircArrayQueue ca;

        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
        for (int i = 1; i <= iterations; i++)
        {
            ca.enqueue(i);
        }
        chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
        cout << "Elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl;
    }

/*

  // Testing functions

    LinkedListQueue ll;
    cout << "ll.peek(): " << ll.peek() << endl;
    cout << "ll.size(): " << ll.size() << endl;
    ll.dequeue();
    ll.enqueue(1);
    ll.enqueue(2);
    ll.enqueue(3);
    ll.enqueue(4);
    ll.enqueue(5);
    ll.display();
    ll.dequeue();
    ll.display();
    ll.enqueue(6);
    ll.display();
    cout << "ll.peek(): " << ll.peek() << endl;
    cout << "ll.size(): " << ll.size() << endl;

    cout << endl;

    CircArrayQueue ca;
    cout << "ca.peek(): " << ca.peek() << endl;
    cout << "ca.size(): " << ca.size() << endl;
    ca.dequeue();
    ca.enqueue(1);
    ca.enqueue(2);
    ca.enqueue(3);
    ca.enqueue(4);
    ca.enqueue(5);
    ca.display();
    ca.dequeue();
    ca.display();
    ca.enqueue(6);
    ca.display();
    cout << "ca.peek(): " << ca.peek() << endl;
    cout << "ca.size(): " << ca.size() << endl;
*/

    return 0;
}
