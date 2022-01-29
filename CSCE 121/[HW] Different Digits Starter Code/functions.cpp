#include "functions.h"

bool is_valid_range(int a, int b) {
    // TODO(student): validate input range

    if (0 < a && a <= b && b <= 10000)
      return true;
    else
      return false;
}

int count_digit_occurrences(int number, int digit) {
  // TODO(student): return how many times digit occurs in number

  int count = 0;
  if (number == 0 && digit == 0)
    count = 1;

  if (number < 0)
    number *= -1;

  while(number > 0)
  {
    if ((number % 10) == digit)
      count++;
    number /= 10;
  }
  return count;
}

bool has_repeated_digits(int number) {
    // TODO(student): return true if number has repeated digits
    for (int i=0; i <= 9; i++)
    {
      if (count_digit_occurrences(number, i) >= 2)
        return true;
    }

    return false;
}

int count_valid_numbers(int a, int b) {
    // TODO(student): return count of valid numbers in range

    int count = 0;
    for (int i = a; i <= b; i++)
    {
      if (has_repeated_digits(i))
        count++;
    }
    return count;
}
