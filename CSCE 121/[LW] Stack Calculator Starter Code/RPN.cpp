#include <cmath>
#include <iostream>
#include <string>
#include "Stack.h"

using namespace std;
int main()
{
  string input;

  Stack myStack;

  double left;
  double right;
  double number;

  bool invalid = false;
  while(input != "="){
    cin >> input;
    if(input == "^"){
      invalid = true;
    }
    else if((input != "+") && (input != "-") && (input != "*") && (input != "/") && (input != "="))
    {
      number = stod(input);
      push(myStack, number);
    }
    else if(input == "+")
    {
      right = pop(myStack);
      left = pop(myStack);
      number = right + left;
      push(myStack, number);
    }
    else if(input == "-")
    {
      right = pop(myStack);
      left = pop(myStack);
      number = left - right;
      push(myStack, number);
    }
    else if(input == "*")
    {
      right = pop(myStack);
      left = pop(myStack);
      number = right * left;
      push(myStack, number);
    }
    else if(input == "/")
    {
      right = pop(myStack);
      left = pop(myStack);
      number = left / right;
      push(myStack, number);
    }
  }
  double output = myStack.A[0];
  if(invalid)
    cout << "[ERROR] invalid operator: ^" << endl;
  else
    cout << output << endl;
  delete [] myStack.A;
  return 0;
}
