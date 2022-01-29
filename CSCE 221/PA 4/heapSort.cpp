#include <vector>
#include <iostream>

using namespace std;

template <class T>

void rearrange(vector<T>& heap, int currIndex, int size) // recursively "bubbles up" through tree
{
  if (2 * currIndex >= size - 1)
    return; // this means that no rearranging is required

  int curr = heap[currIndex];

  int leftChildIndex = 2 * currIndex;
  int leftChild = heap[leftChildIndex];

  int rightChildIndex = 2 * currIndex + 1;
  int rightChild = heap[rightChildIndex];

  if (curr < leftChild || curr < rightChild) // children are larger -> swap will be made
  {
    if (leftChild > rightChild) // determine which child to swap with
    {
      swap(heap[currIndex], heap[leftChildIndex]);
      rearrange(heap, leftChildIndex, size); // rearrange from the left child, the element that was just swapped
    }
    else
    {
      swap(heap[currIndex], heap[rightChildIndex]);
      rearrange(heap, rightChildIndex, size); // rearrange from the right child, the element that was just swapped
    }
  }
}

template <class T>

bool checkVector(vector<T> heap)
{
  if (heap[0] != -1)
  {
    cout << "Vector is implemented incorrectly - there should be a -1 at index 0." << endl;
    return false;
  }
  else
    return true;
}

template <class T>

void buildHeap(vector<T>& heap)
{
  if (!checkVector(heap))
    return;

  for (int currIndex = (heap.size() - 1) / 2; currIndex > 0; currIndex--)
  {
    rearrange(heap, currIndex, heap.size());
  }
  // swap(heap[1], heap[heap.size() - 1]);
}

template <class T>

void deleteMax(vector<T>& heap, int size)
{
  if (!checkVector(heap))
    return;

  swap(heap[1], heap[size + 1]);
  rearrange(heap, 1, size);
}

template <class T>

void heapSort(vector<T>& heap)
{
  // int size = heap.size() - 1;
  for (int i = heap.size() - 1; i > 0 ; i--)
  {
    swap(heap[1], heap[i]);
    rearrange(heap, 1, i);
  }
  if (heap[1] > heap[2]) // accounts for difference in odd vs. even sized cases
    swap(heap[1], heap[2]);
  if (heap[heap.size() - 2] > heap[heap.size() - 1])
    swap(heap[heap.size() - 2], heap[heap.size() - 1]);
}

#include <random>
#include <algorithm>
#include <iterator>
#include <functional>
#include <chrono>

int main()
{

  string response;
  cout << "Select List Generation - Type \"1\" for Random Values, \"2\" for Increasing Order, or \"3\" for Decreasing Order: ";
  cin >> response;

  int iterations = 1000000000;
  vector<int> heap1(iterations + 1);

  // random generation of integers

  if (response == "1")
  {
    random_device rnd_device;
    mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    uniform_int_distribution<int> dist {1, 52};

    auto gen = [&dist, &mersenne_engine](){
                   return dist(mersenne_engine);
               };

    generate(begin(heap1), end(heap1), gen);

    heap1[0] = -1;
    cout << "Random Generation of " << iterations << " ints." << endl;
  }

  // increasing order generation of integers

  if (response == "2")
  {
    for (int i = 1; i <= iterations; i++)
      heap1[i] = i;
    heap1[0] = -1;
    cout << "Increasing Order Generation of " << iterations << " ints." << endl;
  }

  // decreasing order generation of integers

  if (response == "3")
  {
    for (int i = iterations; i > 0; i--)
      heap1[iterations - i + 1] = i;
    heap1[0] = -1;
    cout << "Decreasing Order Generation of " << iterations << " ints." << endl;
  }

  chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();


  buildHeap(heap1);

  heapSort(heap1);


  chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //end clock
  cout << "heapSort time elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl; //take delta time in microseconds


  // testing functions

  // vector<int> heap1{-1,1,4,5,7,8,2,8,534,8,4358,23,5,72};
  //
  // cout << "Unsorted list: " << endl;
  // for (int i = 1; i < heap1.size(); i++)
  //     cout << heap1[i] << " ";
  // cout << endl;
  //
  // buildHeap(heap1);
  //
  // cout << "Sorted into heap: " << endl;
  // for (int i = 1; i < heap1.size(); i++)
  //     cout << heap1[i] << " ";
  // cout << endl;
  //
  // // deleteMax(heap1, heap1.size() - 3);
  // //
  // // cout << "After 2nd deleteMax: " << endl;
  // // for (int i = 1; i < heap1.size(); i++)
  // //     cout << heap1[i] << " ";
  // // cout << endl;

  // heapSort(heap1);
  //
  // cout << "After heapSort: " << endl;
  // for (int i = 1; i < heap1.size(); i++)
  //     cout << heap1[i] << " ";
  // cout << endl;

  // vector <int> heap2{};
  //
  // cout << "Unsorted list: " << endl;
  // for (int i = 1; i < heap2.size(); i++)
  //     cout << heap2[i] << " ";
  // cout << endl;
  //
  // buildHeap(heap2);
  //
  // cout << "Sorted into heap: " << endl;
  // for (int i = 1; i < heap2.size(); i++)
  //     cout << heap2[i] << " ";
  // cout << endl;
  //
  // heapSort(heap2);
  //
  // cout << "After heapSort: " << endl;
  // for (int i = 1; i < heap2.size(); i++)
  //     cout << heap2[i] << " ";
  // cout << endl;


  return 0;
}
