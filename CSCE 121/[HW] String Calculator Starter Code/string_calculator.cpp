#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {

    int intDecimal;
    if (digit >= '0' && digit <= '9')
      intDecimal = digit - '0';
    else
      throw std::invalid_argument("Invalid Argument");

    return intDecimal;
}

char decimal_to_digit(unsigned int decimal) {

    char charDigit;

    if (decimal < 10)
      charDigit = '0' + decimal;
    else
      throw std::invalid_argument("Invalid Argument");

    return charDigit;
}

string trim_leading_zeros(string num) {

    bool negative = false;
    if (num.at(0) == '-')
    {
      num.erase(0,1);
      negative = true;
    }
    while(num.at(0) == '0' && num.size() > 1)
    {
      num.erase(0,1);
    }

    if(negative && num != "0")
    {
      num.insert(0,1,'-');
    }

    return num;
}

string add(string lhs, string rhs) {

    string left = trim_leading_zeros(lhs);
    string right = trim_leading_zeros(rhs);

    bool leftNeg = false;
    bool rightNeg = false;

    if (left.at(0) == '-')
    {
      left.erase(0,1);
      leftNeg = true;
    }

    if (right.at(0) == '-')
    {
      right.erase(0,1);
      rightNeg = true;
    }

    bool bothNeg = (rightNeg && leftNeg);

    while(right.size() < left.size())
      right.insert(0,1,'0');

    while(right.size() > left.size())
      left.insert(0,1,'0');

    string sum = "";

    // Covers ++ and -- addition
    if ((left.size() >= right.size()) && (((!leftNeg) && (!rightNeg)) || ((leftNeg) && (rightNeg))))
    {
      bool carry = false;
      for (int i = left.size()-1; i >= 0; i--)
      {

        // cout << "left is " << left << endl;
        // cout << "right is " << right << endl;

        int digit = 0;
        int leftDig = digit_to_decimal(left.at(i));
        int rightDig = digit_to_decimal(right.at(i));

        if (carry)
        {
          digit = 1;
          carry = false;
        }

        if (leftDig + rightDig + digit >= 10)
          carry = true;

        digit = (leftDig + rightDig + digit) % 10;
        sum.insert(0,1,decimal_to_digit(digit));

        left.erase(i,1);
        right.erase(i,1);
      }

      if (carry)
      sum.insert(0,1,'1');

      if(bothNeg)
        sum.insert(0,1,'-');

    }


    // Covers +- or -+ addition
    if((left.size() >= right.size()) && (((!leftNeg) && (rightNeg)) || ((leftNeg) && (!rightNeg))))
    {
      bool leftBigger;
      bool carry = false;
      for(long unsigned int i = 0; i < left.size(); i++)
      {
        if(left.at(i) != right.at(i))
        {
          int greater = digit_to_decimal(left.at(i)) -   digit_to_decimal(right.at(i));
          leftBigger = greater > 0;
          break;
        }
      }

      if (leftNeg && !rightNeg)
      {
        string temp = right;
        right = left;
        left = temp;
      }

      string rightComp = "";
      for (int i = right.size() - 1; i >= 0; i--)
      {
        rightComp.insert(0,1, decimal_to_digit((9 - digit_to_decimal(right.at(i)))));
      }

      right = rightComp;

      // cout << "left is bigger " << leftBigger << endl;

      for (int i = left.size()-1; i >= 0; i--)
      {
        // cout << "left is " << left << endl;
        // cout << "right is " << right << endl;

        int digit = 0;
        int leftDig = digit_to_decimal(left.at(i));
        int rightDig = digit_to_decimal(right.at(i));

        if (carry)
        {
          digit = 1;
          carry = false;
        }

        if (leftDig + rightDig + digit >= 10)
          carry = true;

        digit = (leftDig + rightDig + digit) % 10;
        sum.insert(0,1,decimal_to_digit(digit));

        left.erase(i,1);
        right.erase(i,1);
      }
      // Check if we need to switch to complement
      if (carry)
      {
        string tempSum = sum;
        sum = "";
        string one = "0";
        for (long unsigned int i = 0; i < tempSum.size() - 1; i++)
          one.insert(0,1,'0');
        // cout << "this is one here " << one << endl;
        for (int i = tempSum.size()-1; i >= 0; i--)
        {
          // cout << "sum is " << tempSum << endl;
          // cout << "one is " << one << endl;

          int digit = 0;
          int leftDig = digit_to_decimal(tempSum.at(i));
          int rightDig = digit_to_decimal(one.at(i));

          if (carry)
          {
            digit = 1;
            carry = false;
          }

          if (leftDig + rightDig + digit >= 10)
            carry = true;

          digit = (leftDig + rightDig + digit) % 10;
          sum.insert(0,1,decimal_to_digit(digit));

          tempSum.erase(i,1);
          one.erase(i,1);
        }
        sum = trim_leading_zeros(sum);
      }
      else
      {
        string sumComp = "";
        for (int i = sum.size() - 1; i >= 0; i--)
        {
          sumComp.insert(0,1, decimal_to_digit((9 - digit_to_decimal(sum.at(i)))));
        }
        // cout << "sum is " << sum << endl;
        sum = sumComp;
        sum = trim_leading_zeros(sum);
        // cout << "now sum is " << sum << endl;

        if (sum != "0")
        {
          if(leftBigger && leftNeg)
            sum.insert(0,1,'-');
          if(!leftBigger && rightNeg)
            sum.insert(0,1,'-');
        }

      }

    }

    return sum;
}

string subtract(string lhs, string rhs) {
    // TODO(student): implement
    if (rhs.at(0) == '-')
      rhs.erase(0,1);
    else
      rhs.insert(0,1,'-');
    string ans = add(lhs, rhs);
    return ans;
}

string multiply(string lhs, string rhs) {
    // TODO(student): implement

    string left = trim_leading_zeros(lhs);
    string right = trim_leading_zeros(rhs);

    bool leftNeg = false;
    bool rightNeg = false;

    if (left.at(0) == '-')
    {
      left.erase(0,1);
      leftNeg = true;
    }

    if (right.at(0) == '-')
    {
      right.erase(0,1);
      rightNeg = true;
    }

    while(right.size() < left.size())
      right.insert(0,1,'0');

    while(right.size() > left.size())
      left.insert(0,1,'0');

    string sum = "";

    // Covers all multiplication
    if ((left.size() >= right.size()))
    {

      int iterations = 0;

      for (int i = left.size() - 1; i >= 0; i--)
      {

        int rightDig = digit_to_decimal(right.at(i));

        string temp = "";
        for (int k = 0; k < iterations; k++)
          temp.insert(0,1,'0');
        int topDigit;
        int newDigit;
        int remainder = 0;
        string tempLeft = left;



        for (int j = left.size() - 1; j >= 0; j--)
        {
          topDigit = digit_to_decimal(tempLeft.at(j));
          newDigit = (rightDig * topDigit + remainder) % 10;
          remainder = (rightDig * topDigit + remainder) / 10;

          temp.insert(0,1,decimal_to_digit(newDigit));

          tempLeft.erase(j,1);

        }

        if (remainder != 0)
          temp.insert(0,1,decimal_to_digit(remainder));


        while(sum.size() < temp.size())
          sum.insert(0,1,'0');

        while(sum.size() > temp.size())
          temp.insert(0,1,'0');


        sum = add(sum,temp);

        iterations ++;
      }

      if(leftNeg ^ rightNeg)
        sum.insert(0,1,'-');

    }

    sum = trim_leading_zeros(sum);

    return sum;
}
