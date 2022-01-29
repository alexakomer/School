#ifndef TAXI_TRIPS_H
#define TAXI_TRIPS_H
#include <string>
using std::string;

/* Global constant for max number of trips in the file
*/
const unsigned int MAX_TRIPS = 10000;

/*
returns true if type is one of the type values in array valid_types
input:  type - string with payment type that we are checking for validity
        valid_types - array of strings listing the valid types
        size - the number of elements in array valid_types
output: returns true if string type appears in array valid_types and
        false otherwise
        if size is zero, it throws std::invalid_argument
*/
bool is_payment_valid(string type, string valid_types[],
                      unsigned int size);

/*
returns the max number in an array
input: values  - an array of double non-negative numbers
       size - the number of elements in the array
output: the largest number that appears in the array.
        if size is zero, it throws std::invalid_argument
*/
double max(double values[], unsigned int size);

/*
returns the min number in an array
input: values  - an array of double non-negative numbers
       size - the number of elements in the array
output: the smallest number that appears in the array.
        if size is zero, it throws std::invalid_argument
*/
double min(double values[], unsigned int size);

/*
returns the average of the numbers in an array
input: values  - an array of double non-negative numbers
       size - the number of elements in the array
output: the average of the numbers in the array.
        if size is zero, it throws std::invalid_argument 
*/
double average(double values[], unsigned int size);

/*
returns the mode of the numbers in the array. If there are
multiple values for mode (i.e., multiple occur most frequently),
the function returns the first of them.

input: values  - an array of double non-negative numbers
       size - the number of elements in the array
output: the mode of the numbers in the array
        if size is zero, it throws std::invalid_argument 
*/
double mode(double values[], unsigned int size);

/*
returns the length of the longest sequence of zeroes in the array
input: values  - an array of double non-negative numbers
       size - the number of elements in the array
output: the length of the longest zero sequence in the array
        if size is zero, it throws std::invalid_argument 
*/
unsigned int length_longest_seq_zeros(double values[],
							 unsigned int size);

#endif  // TAXI_TRIPS_H
