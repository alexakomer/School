#include <iostream>
#include <limits>

using namespace::std;

int recursiveCount(int num)
{
  if (num == 0 || num == 1)
    return num;
  else if (num % 2 == 1)
    return recursiveCount(num / 2) + 1;
  else
    return recursiveCount(num / 2);
}

int main()
{

  int number = 0;
  cout << "Enter a nonnegative numnber: ";
  cin >> number;
  cout << endl;

  int count = recursiveCount(number);
  cout << "The number of ones in its binary representation: " << count << endl;

  return 0;
}
