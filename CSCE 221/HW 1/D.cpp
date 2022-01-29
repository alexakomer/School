// a) Write a program to determine if a positive integer, N, is prime.

bool prime test(int N)
{
  if (N == 1 || N == 2)
    return true;
  if ( N % 2 == 0 )
    return false; p
  for(int i = 3; i < N; i = i + 2) if ( N%i == 0)
    return false;
  return true;
}

// b)
// One for loop, which iterates p at most N times, with a constant amount of work each time. Therefore, O( N).

// c)
// With x bits one can represent any number from 0 up to 2x + 1. Therefore N can be represented with O(log2N) bits.

// e)
// > A 20-bit number can be tested in time approximately 2^2 = 2^10.
// > A 40-bit number can be tested in time approximately 2^2 = 2^20.
// observe that 2^20=(2^10)^2

// f)
// > B is better because it more accurately measures the size of the input.
