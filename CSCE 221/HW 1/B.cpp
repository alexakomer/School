// 2.7 For each of the following six program fragments:
// a. Give an analysis of the running time (Big-Oh will do).

(1) sum = 0;
    for( i = 0; i < n; ++i )
      ++sum;

// Running time is O(n)
// At each new row we have doubled the input size, so we would expect the experimental growth rate to approach 2, which it does.

(2) sum = 0;
    for( i = 0; i < n; ++i )
      for( j = 0; j < n; ++j )
        ++sum;

// Running time is O(n^2)
// At each new row we have doubled the input size, so we would expect the experimental growth rate to approach 2^2, which it does.

(3) sum = 0;
    for( i = 0; i < n; ++i )
      for( j = 0; j < n * n; ++j )
        ++sum;

// Running time is O(n^3)
// At each new row we have doubled the input size, so we would expect the experimental growth rate to approach 2^3 ,which it does.

(4) sum = 0;
    for( i = 0; i < n; ++i )
      for( j = 0; j < i; ++j )
        ++sum;

// Running time is O(n^2)
// At each new row we have doubled the input size, so we would expect the experimental growth rate to approach 2^2, which it does.

(5) sum = 0;
    for( i = 0; i < n; ++i )
      for( j = 0; j < i * i; ++j )
        for( k = 0; k < j; ++k )
          ++sum;

// Running time is O(n^5)
// At each new row we have doubled the input size, so we would expect the experimental growth rate to approach 2^5, which it does.

(6) sum = 0;
    for( i = 1; i < n; ++i )
      for( j = 1; j < i * i; ++j )
        if( j % i == 0 )
          for( k = 0; k < j; ++k )
            ++sum;

// Running time is O(n^4)
// At each new row we have doubled the input size, so we would expect the experimental growth rate to approach 2^4, which it does.
