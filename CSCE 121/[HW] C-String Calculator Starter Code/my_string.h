// my_string.h
#ifndef MY_STRING_H
#define MY_STRING_H

#include <iostream>

// these are useful for debugging
// to turn them on, remove the ;//
// to turn them off again, put the ;// back
#define DEBUG(X) ;//std::cout << "[DEBUG] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " = " << X << std::endl;
#define INFO(X) ;//std::cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << X << std::endl;

class my_string {
    char* _data;
    size_t _capacity;
    size_t _size;

 public:
    // types
    using size_type = size_t;
    static const size_type npos  = -1;

 private:   
    // TODO(student): declare private (helper) methods here
    
 public:
    // constructors
    //   default
    my_string();
    //   rule of 3
    //     my_string copy constructor
    my_string(const my_string& other);
    //     my_string copy assignment
    my_string& operator=(const my_string& rhs);
    //     destructor
    ~my_string();
    //   c-string copy constructor (teams up with my_string copy assignment to handle c-string copy assignment)
    my_string(const char* other);
    
    // element access
    //   note: the const versions have the same implementation (copy+paste) as the non-const versions
    const char& front() const;
    char& front();
    const char& at(size_type index) const;
    char& at(size_type index);
    const char& operator[](size_type index) const;
    char& operator[](size_type index);
    // TODO(student): declare other necessary access methods here, if any
    
    // capacity
    bool empty() const;
    size_type size() const;
    // TODO(student): declare other necessary capacity methods here, if any
    
    // operations
    //   concatenation
    //     note: the friends are non-member functions with the benefits of access to the private parts of my_string
    friend my_string operator+(my_string lhs, const my_string& rhs);
    friend my_string operator+(my_string lhs, const char* rhs);
    friend my_string operator+(my_string lhs, char rhs);
    friend my_string operator+(const char* lhs, const my_string& rhs);
    friend my_string operator+(char lhs, my_string rhs);
    my_string& operator+=(const my_string& rhs);
    my_string& operator+=(const char* rhs);
    my_string& operator+=(char rhs);
    // TODO(student): declare other necessary operation methods here, if any
    
    // search
    size_type find(const my_string& str, size_type pos = 0) const;
    // TODO(student): declare other necessary search methods here, if any
    
};

// non-member functions

// relational operators
bool operator==(const my_string& lhs, const my_string& rhs);
bool operator==(const my_string& lhs, const char* rhs);
// TODO(student): declare other necessary relational operators here, if any

// stream operators (I/O)
std::ostream& operator<<(std::ostream& os, const my_string& str);
std::istream& operator>>(std::istream& os, my_string& str);
std::istream& getline(std::istream& is, my_string& str, char delim='\n');

// numeric conversions
my_string to_string(int val);
// TODO(student): declare other necessary numeric conversions here, if any

#endif  // MY_STRING_H
