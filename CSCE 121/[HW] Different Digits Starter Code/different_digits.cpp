#include <iostream>
#include <limits>
#include "functions.h"

using std::cout, std::cin, std::endl;

int main() {
    // TODO(student): print prompt for input

    cout << "Enter numbers 0 < a <= b <= 10000: ";

    // TODO(student): read the numbers from standard input

    int low, high;
    cin >> low;
    cin >> high;

    cout << endl;

    // TODO(student): validate input (and reprompt on invalid input)

    bool valid = is_valid_range(low,high);

    while (!valid)
    {
      cout << "Invalid input" << endl;
      cout << "Enter numbers 0 < a <= b <= 10000: ";

      cin >> low;
      cin >> high;

      cout << endl;

      valid = is_valid_range(low,high);
    }

    // TODO(student): compute and display solution

    int numOccurences = count_valid_numbers(low, high);

    cout << "There are " << numOccurences << " valid numbers between "
    << low << " and " << high << endl;

    return 0;
}
