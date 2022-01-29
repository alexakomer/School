#include <stdexcept>
#include <string>
using std::string, std::invalid_argument;
#include "taxi_trips.h"
#include <iostream>

bool is_payment_valid(string type, string valid_types[], unsigned int size) {
  // TODO(student): implement

  if (size == 0)
    throw invalid_argument("Size is 0");

  bool found = false;
  for (unsigned int i = 0; i < size; i++)
  {
    if (type == valid_types[i])
    {
      found = true;
      break;
    }
  }
  return found;
}

double max(double values[], unsigned int size) {
  // TODO(student): implement

  if (size == 0)
    throw invalid_argument("Size is 0");

  double maximum = 0;
  for (unsigned int i = 0; i < size; i++)
  {
    if (values[i] >= maximum)
      maximum = values[i];
  }
  return maximum;
}

double min(double values[], unsigned int size) {
  // TODO(student): implement

  if (size == 0)
    throw invalid_argument("Size is 0");

  double minimum = 2147483647;
  for (unsigned int i = 0; i < size; i++)
  {
    if (values[i] <= minimum)
      minimum = values[i];
  }
  return minimum;

}

double average(double values[], unsigned int size) {
  // TODO(student): implement

  if (size == 0)
    throw invalid_argument("Size is 0");

  double sum = 0;
  for (unsigned int i = 0; i < size; i++)
    sum += values[i];

  double avg = sum / size;

  return avg;
}

double mode(double values[], unsigned int size) {
  // TODO(student): implement

  if (size == 0)
    throw invalid_argument("Size is 0");

  int mostOccurences = 0;
  double mode = 0;
  for (unsigned int i = 0; i < size; i++)
  {
    int count = 0;
    double val = values[i];
    for (unsigned int j = i; j < size; j++)
    {
      if (val == values[j])
        count += 1;
    }
    if (count > mostOccurences)
    {
      mostOccurences = count;
      mode = val;
    }
  }

  return mode;
}

unsigned int length_longest_seq_zeros(double values[], unsigned int size) {
  // TODO(student): implement

  if (size == 0)
    throw invalid_argument("Size is 0");

  unsigned int mostConsecZeros = 0;
  for (unsigned int i = 0; i < size; i++)
  {
    unsigned int consecZeros = 0;
    if (values[i] == 0)
    // std::cout << "Accessed a 0 at " << i << std::endl;
    {
      unsigned int j = i;
      while (values[j] == 0 && j < size)
      {
        consecZeros += 1;
        j += 1;
      }
      if (consecZeros >= mostConsecZeros)
      {
        mostConsecZeros = consecZeros;
        // std::cout << "Reassigned most zeroes at " << i << " which is: " << mostConsecZeros << std::endl;
      }
    }
  }
  // std::cout << "This one " << mostConsecZeros << std::endl;
  return mostConsecZeros;
}
