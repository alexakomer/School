#include <string>
#include <iostream>
#include "AttendanceRecord.h"
#include "Date.h"

using std::cout, std::string;

AttendanceRecord::AttendanceRecord(std::string course_idTemp, std::string student_idTemp, Date timeTemp)
{
  course_id = course_idTemp;
  student_id = student_idTemp;
  time = timeTemp;
}

string AttendanceRecord::getCourseID() const
{
  return course_id;
}

string AttendanceRecord::getStudentID() const
{
  return student_id;
}

Date AttendanceRecord::getDate() const
{
  return time;
}
