#include <vector>
#include <iostream>

using namespace std;

template <class T>

// "divide" from divide and conquer
int division(vector<T>& array, int leftIndex, int rightIndex, int pivotKey)
{
  while (leftIndex <= rightIndex)
  {
    while (array[leftIndex] < pivotKey) // iterate left pointer until it is larger than pivot and ready to swap
      leftIndex++;
    while (array[rightIndex] > pivotKey) // iterate right pointer until it is smaller than pivot and ready to swap
      rightIndex--;
    if (leftIndex <= rightIndex)
    {
      swap(array[leftIndex], array[rightIndex]); // perform swap and continue iterating through each division
      leftIndex++;
      rightIndex--;
    }
  }
  return leftIndex;
}

template <class T>

// explicit function that calls recursive division function
void quickSort(vector<T>& array, int leftIndex, int rightIndex)
{
  if (leftIndex >= rightIndex) // once indices cross, base case is reached and sort is finished
    return;
  int pivotKey = array[leftIndex]; // select first element of each division as the pivot
  int index = division(array, leftIndex, rightIndex, pivotKey); // index where divisions will be separataed
  quickSort(array, leftIndex, index - 1); // recursively call left division
  quickSort(array, index, rightIndex); // recursively call right division
}

template <class T>

void quickSort(vector<T>& array) // simpler function call that gives default information before first division
{
  quickSort(array, 0, array.size() - 1);
}

#include <random>
#include <algorithm>
#include <iterator>
#include <functional>
#include <chrono>

int main ()
{

  string response;
  cout << "Select List Generation - Type \"1\" for Random Values, \"2\" for Increasing Order, or \"3\" for Decreasing Order: ";
  cin >> response;

  int iterations = 1000000000;
  vector<int> array(iterations + 1);

  // random generation of integers

  if (response == "1")
  {
    random_device rnd_device;
    mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    uniform_int_distribution<int> dist {1, 52};

    auto gen = [&dist, &mersenne_engine](){
                   return dist(mersenne_engine);
               };

    generate(begin(array), end(array), gen);

    array[0] = -1;
    cout << "Random Generation of " << iterations << " ints." << endl;
  }

  // increasing order generation of integers

  if (response == "2")
  {
    for (int i = 1; i <= iterations; i++)
      array[i] = i;
    array[0] = -1;
    cout << "Increasing Order Generation of " << iterations << " ints." << endl;
  }

  // decreasing order generation of integers

  if (response == "3")
  {
    for (int i = iterations; i > 0; i--)
      array[iterations - i + 1] = i;
    array[0] = -1;
    cout << "Decreasing Order Generation of " << iterations << " ints." << endl;
  }

  chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();


  quickSort(array);


  chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //end clock
  cout << "first element pivot quickSort time elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl; //take delta time in microseconds


  // testing functions

  // vector<int> array{0, 15, 16, 72, 13, 6, 91, 4};
  //
  // cout << "Unsorted list: " << endl;
  // for (int i = 0; i < array.size(); i++)
  //     cout << array[i] << " ";
  // cout << endl;
  //
  // quickSort(array);
  //
  // cout << "Sorted list: " << endl;
  // for (int i = 0; i < array.size(); i++)
  //     cout << array[i] << " ";
  // cout << endl;
  //
  // vector <int> array2{};
  //
  // cout << "Unsorted list: " << endl;
  // for (int i = 1; i < array2.size(); i++)
  //     cout << array2[i] << " ";
  // cout << endl;
  //
  // quickSort(array2);
  //
  // cout << "Sorted list: " << endl;
  // for (int i = 1; i < array2.size(); i++)
  //     cout << array2[i] << " ";
  // cout << endl;

  return 0;
}
