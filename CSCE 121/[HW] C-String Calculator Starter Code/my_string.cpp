// my_string.cpp
#include <iostream>
#include "my_string.h"
#include "my_sstream.h"

// TODO(student): define all necessary my_string methods
// NOTE: some methods suggested here may not be required for you.
//       if you don't need a method, then you are not required to implement it
// NOTE: some methods not suggested here may be required for you.
//       if you need a method, then you are required to implement it (or re-engineer your solution to no longer need the method).

// my_string methods

// constructors
//   default (done for you.  you're welcome.)
my_string::my_string() : _data(new char[1]{0}), _capacity(1), _size(0) {}
//   rule of "3"

//     my_string copy constructor
my_string::my_string(const my_string& other) : my_string() {
  this->_capacity = other._capacity;
  this->_size = other._size;
  delete[] this->_data;
  this->_data = new char[other._capacity]{0};

  for (size_t i = 0; i < _size; i++)
    _data[i] = other._data[i];

  // *_data = *other._data;

}

//     my_string copy assignment
my_string& my_string::operator=(const my_string& rhs)
{
  if (this != &rhs)
  {
    _size = rhs._size;
    _capacity = rhs._capacity;

    delete [] _data;

    // _data = new char[_size]{0};
    //
    // for (size_t i = 0; i < _size; i++)
    //   _data[i] = rhs._data[i];

    *_data = *rhs._data;
  }
  return *this;
}

//     destructor
my_string::~my_string()
{
  delete [] _data;
}

//   c-string copy constructor
my_string::my_string(const char* other) : my_string()
{
  _data = new char[_size]{0};

  for (size_t i = 0; i < _size; i++)
    _data[i] = other._data[i];
}


// size functions for c-string copies
my_string::size_type charSize(char* arr) { //return size of pointer to char array
    my_string::size_type i = 0;
    while (arr[i] != '\000') {
        i++;
    }
    return i;
}
my_string::size_type charSize(const char* arr) {
    my_string::size_type i = 0;
    while (arr[i] != '\000') {
        i++;
    }
    return i;
}




// element access
//   at
const char& my_string::at(size_t index) const
{
  if (index > my_string._size)

}

char& my_string::at(size_t index)
{
  if (index > my_string._size)

}




//   front
//   operator[]

// capacity
//   empty
//   size

size_t my_string::size()
{

}

// operations
//   concatenation
//     my_string + my_string (non-member, friend)
//     my_string + c-string (non-member, friend)
//     my_string + char (non-member, friend)
//     c-string + my_string (non-member, friend)
//     char + my_string (non-member, friend)
//     my_string += my_string
//     my_string += c-string
//     my_string += char

// search
//   find

// non-member functions
//   relational operators
//     my_string == my_string
//     my_string == c-string
//   stream operators
//     ostream instertion operator
//     istream extraction operator
//     getline
//   numeric conversions
//     to_string


// my_istringstream methods

// my_istringstream::my_istringstream(const my_string& str) : _str(str), idx(0), state_fail(false), state_eof(str.empty()) {}
//
// void my_istringstream::eat_whitespaces() {
//     while (idx < _str.size() && isspace(_str[idx])) {
//         idx++;
//     }
// }
//
// my_istringstream& my_istringstream::operator>>(my_string& str) {
//     eat_whitespaces();
//     if (eof()) {
//         state_fail = true;
//     }
//     if (fail()) {
//         return *this;
//     }
//     my_string s;
//     while (idx < _str.size() && !isspace(_str[idx])) {
//         s += _str[idx++];
//     }
//     if (idx == _str.size()) {
//         state_eof = true;
//     }
//     str = s;
//     return *this;
// }
//
// my_istringstream& my_istringstream::operator>>(char& c) {
//     eat_whitespaces();
//     if (eof()) {
//         state_fail = true;
//     }
//     if (fail()) {
//         return *this;
//     }
//     if (idx < _str.size()) {
//         c = _str[idx++];
//     }
//     if (idx == _str.size()) {
//         state_eof = true;
//     }
//     return *this;
// }
//
// bool my_istringstream::good() const { return !(state_fail || state_eof); }
// bool my_istringstream::fail() const { return state_fail; }
// bool my_istringstream::eof() const { return state_eof; }

// TODO(student): define other my_istringstream methods, if any
