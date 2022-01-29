#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include "Date.h"

using std::string, std::stringstream, std::setw,  std::setfill;

Date::Date() : year(0), month(0), day(0), hour(0), min(0), sec(0) {}

Date::Date(int year, int month, int day, int hour, int min, int sec)
{
  this->year = year;
  this->month = month;
  this->day = day;
  this->hour = hour;
  this->min = min;
  this->sec = sec;
}

Date::Date(int hour, int min, int sec)
{
  this->year = 0;
  this->month = 0;
  this->day = 0;
  this->hour = hour;
  this->min = min;
  this->sec = sec;
}

bool Date::operator<(const Date& rhs) const {

  if ((this -> year == 0 && this -> month == 0 && this -> day == 0) || (rhs.year == 0 && rhs.month == 0 && rhs.day == 0))
  {
    if (this -> hour < rhs.hour)
      return true;
    else if (this -> hour > rhs.hour)
      return false;

    if (this -> min < rhs.min)
      return true;
    else if (this -> min > rhs.min)
      return false;

    if (this -> sec < rhs.sec)
      return true;
  }
  else
  {
    if (this -> year < rhs.year)
      return true;
    else if (this -> year > rhs.year)
      return false;

    if (this -> month < rhs.month)
      return true;
    else if (this -> month > rhs.month)
      return false;

    if (this -> day < rhs.day)
      return true;
    else if (this -> day > rhs.day)
      return false;

    if (this -> hour < rhs.hour)
      return true;
    else if (this -> hour > rhs.hour)
      return false;

    if (this -> min < rhs.min)
      return true;
    else if (this -> min > rhs.min)
      return false;

    if (this -> sec < rhs.sec)
      return true;
  }

    return false;
}

// methods below are provided to students

string Date::getDateTime() const {
  stringstream ss;
  ss << month << "/" << day << "/" << year << " ";
  ss << setw(2) << setfill('0') << hour << ":";
  ss << setw(2) << setfill('0') << min << ":";
  ss << setw(2) << setfill('0') << sec;
  return ss.str();
}

string Date::getDate() const {
  stringstream ss;
  ss << month << "/" << day << "/" << year;
  return ss.str();
}

string Date::getTime(bool withSeconds) const {
  stringstream ss;
  ss << setw(2) << setfill('0') << hour << ":";
  ss << setw(2) << setfill('0') << min;
  if (withSeconds)
    ss << ":" << setw(2) << setfill('0') << sec;
  return ss.str();
}



bool Date::operator>(const Date& rhs) const {
    return rhs < *this;
}

bool Date::operator<=(const Date& rhs) const {
    return !(*this > rhs);
}

bool Date::operator>=(const Date& rhs) const {
    return !(*this < rhs);
}

bool leap_year(unsigned int year) {
  /* From wikipedia: year which is a multiple of 4 (except for years evenly divisible by 100,
   * which are not leap years unless evenly divisible by 400).
   */
  if (year % 400 == 0
      || (year % 4 == 0 && year % 100 != 0)) {
    return true;
  }
  return false;
}

bool Date::isValid() const {
  if (day == 0 || month == 0) {
    return false;
  }
  if (month > 12) {
    return false;
  }
  unsigned int days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31,
                                    31, 30, 31, 30, 31};
  if (leap_year(year)) {
    days_in_month[2] = 29;
  }

  if (day > days_in_month[month]) {
    return false;
  }
  return true;
}
