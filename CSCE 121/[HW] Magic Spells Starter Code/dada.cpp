/*
DADA function definitions
*/

#include <iostream>
#include <cmath>
#include "dada.h"
using std::cout, std::endl, std::abs, std::sqrt;

int amax(const double x[], const unsigned int len) {
    //TODO: student implement code here

    if (len == 0)
      return -1;

    int index = 0;
    double largest = x[0];
    for (unsigned int i = 0; i < len; i++)
    {
      if (abs(x[i]) > largest)
      {
        largest = abs(x[i]);
        index = i;
      }
    }

    return index;
}

double asum(const double x[], const unsigned int len) {
    //TODO: student implement code here

    double sum = 0;
    for (unsigned int i = 0; i < len; i++)
    {
      sum += abs(x[i]);
    }

    return sum;
}

void axpy(const double a, const double x[], double y[], const unsigned int len) {
    //TODO: student implement code here

    for (unsigned int i = 0; i < len; i++)
    {
      y[i] += a * x[i];
    }
}

void copy(const double src[], double dest[], const unsigned int len) {
    //TODO: student implement code here

    for (unsigned int i = 0; i < len; i++)
      dest[i] = src[i];
}

double dot(const double x[], const double y[], const unsigned int len) {
    //TODO: student implement code here

    double dot = 0;
    for (unsigned int i = 0; i < len; i++)
      dot += x[i] * y[i];
    return dot;
}

double norm2(const double x[], const unsigned int len) {
    //TODO: student implement code here

    double sum = 0;
    for (unsigned int i = 0; i < len; i++)
      sum += (pow(x[i],2.0));

    double prod = pow(sum, 0.5);
    return prod;
}

void scale(const double a, double x[], const unsigned int len) {
    //TODO: student implement code here

    for (unsigned int i = 0; i < len; i++)
      x[i] =  a * x[i];
}

void swap(double x[], double y[], const unsigned int len) {
    //TODO: student implement code here

    for (unsigned int i = 0; i < len; i++)
    {
      double temp = x[i];
      x[i] = y[i];
      y[i] = temp;
    }
}
