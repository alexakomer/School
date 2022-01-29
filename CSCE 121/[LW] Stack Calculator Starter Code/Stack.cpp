#include <cmath>
#include <iostream>
#include <string>
#include "Stack.h"

void push(Stack& s, double element){
  if(s.length < s.capacity)
  {
    s.A[s.length] = element;
    s.length += 1;
  }
  else
  {
    int updated_capacity = s.capacity*2;
    double* new_S = new double[updated_capacity];
    for(int i = 0; i < s.length; i++)
      new_S[i] = s.A[i];

    delete [] s.A;

    s.A = new_S;
    s.A[s.length] = element;
    s.length += 1;
    s.capacity = updated_capacity;
  }
}

double pop(Stack& s)
{
  if(s.length == 0)
    return NAN;
  else
  {
    double last_element = s.A[s.length-1];
    s.A[s.length-1] = NAN;
    s.length -= 1;
    return last_element;
  }
}

double peek(const Stack s)
{
  return s.A[s.length -1];
}
