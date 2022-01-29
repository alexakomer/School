// Write the fast exponentiation routine without recursion.

#include <iostream>
#include <limits>

using namespace::std;

int fastExp (int base, int exp)
{
  int num = 1;
  int tempExp = exp;
  int tempBase = base;

  if (exp == 0)
    return 1;

  while (tempExp != 1)
  {
    if (tempExp % 2 == 1)
    {
      num = num * tempBase;
    }
  tempBase = tempBase * tempBase;
  tempExp /= 2;
  }
  return num * tempBase;
}

// int main()
// {
//
//   cout << fastExp(3, 5) << endl;
//
//   return 0;
// }
