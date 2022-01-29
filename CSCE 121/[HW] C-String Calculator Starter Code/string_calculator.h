// string_calculator.h
#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include "my_string.h"

/*
convert a character digit to an integer value
input: digit - a character representing a digit, e.g. '7'
output: the corresponding integer value of the digit, e.g. 7
throws: std::invalid_argument if the input is not a valid digit, e.g. '0' -- '9'
*/
unsigned int digit_to_decimal(char digit);

/*
convert an integer value to a character digit
input: decimal - an integer value of a digit, e.g. 7
output: the corresponding character of the digit, e.g. '7'
throws: std::invalid_argument if the input is not a valid digit, e.g. 0 -- 9
*/
char decimal_to_digit(unsigned int decimal);

/*
remove the leading zeros from a number
input: num - a string representing a number with zero or more leading 0s
output: a copy of the input with all leading 0s removed
throws: none 
*/
my_string trim_leading_zeros(const my_string& num);

/*
add two numbers 
input: lhs,rhs - strings representing numbers, e.g. "1", "2"
output: the result of adding rhs to lhs: lhs + rhs e.g. "3"
throws: none.
*/
my_string add(const my_string& lhs, const my_string& rhs);

/*
subtract two numbers
input: lhs,rhs - strings representing numbers, e.g. "1", "2"
output: the result of subtracting rhs from lhs: lhs - rhs, e.g. "-1"
throws:  none.
*/
my_string subtract(const my_string& lhs, const my_string& rhs);

/*
muplity two numbers
input: lhs,rhs - strings representing numbers, e.g. "1", "2"
output: the result of multiplying lhs by rhs: lhs * rhs, e.g. "2"
throws:  none.
*/
my_string multiply(const my_string& lhs, const my_string& rhs);

#endif  // STRING_CALCULATOR_H
