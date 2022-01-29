// my_ssstream.h
#ifndef MY_SSTREAM_H
#define MY_SSTREAM_H

#include "my_string.h"

class my_istringstream {
    my_string _str;
    my_string::size_type idx;
    bool state_fail;
    bool state_eof;
    
    void eat_whitespaces();
    
 public:
    my_istringstream(const my_string& str);

    my_istringstream& operator>>(my_string& str);
    my_istringstream& operator>>(char& c);

    bool good() const;
    bool fail() const;
    bool eof() const;
    
    // TODO(student): declare other my_istringstream methods, if any
};

#endif  // MY_SSTREAM_H
