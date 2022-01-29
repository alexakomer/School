#include <iostream>
#include "cstring.h"

unsigned int length(char str[]) {
  // returns the length of the string including zero (0)

  int count = 0;

  for (int i = 0; str[i] != '\0'; i++)
    count++;

  return count;
}

unsigned int find(char str[], char character) {
  // returns
  //  - the index of the first occurence of character in str
  //  - the size if the character is not found

  int index = -1;

  for (int i = 0; str[i] != '\0'; i++)
  {
    if (str[i] == character)
      {
        index = i;
        break;
      }
  }

  if (index == -1)
    index = length(str);

  return index;
}

bool equalStr(char str1[], char str2[]) {
  // returns true if they are equal and false if they are not

  bool equal = true;

  if (length(str1) != length(str2))
    return false;

  for (int i = 0; str1[i] != '\0'; i++)
  {
    if (str1[i] != str2[i])
      equal = false;
  }

  return equal;
}
