#include <iostream>
#include <string>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"

using std::string, std::ostream, std::endl, std::cout;

Course::Course(string id,string title, Date startTime, Date endTime)
{
  this->id = id;
  this->title = title;
  this->startTime = startTime;
  this->endTime = endTime;
}

string Course::getID() const
{
  return id;
}

string Course::getTitle() const
{
  return title;
}

Date Course::getStartTime() const
{
  return startTime;
}

Date Course::getEndTime() const
{
  return endTime;
}

void Course::addAttendanceRecord(AttendanceRecord ar)
{
  if((ar.getDate() >= (this-> startTime)) && (ar.getDate() <= (this-> endTime)))
    attendanceRecords.push_back(ar);
  else
    throw std::invalid_argument("AttendanceRecord time is invalid");
}

void Course::outputAttendance(std::ostream& os) const
{
  if (attendanceRecords.empty())
    os << "No records" << endl;
  else
  {
    for (size_t i = 0; i < attendanceRecords.size(); i++)
    {
      os << attendanceRecords.at(i).getDate().getDateTime() << "," << attendanceRecords.at(i).getCourseID();
      os << "," << attendanceRecords.at(i).getStudentID() << endl;
    }
  }
}

void Course::outputAttendance(std::ostream& os, std::string student_id) const
{
  bool isEmpty = true;

  if (attendanceRecords.empty())
  {
    os << "No records" << endl;
    isEmpty = false;
  }

  else
  {
    for (size_t i = 0; i < attendanceRecords.size(); i++)
    {
      if (attendanceRecords.at(i).getStudentID() == student_id)
      {
        isEmpty = false;
        os << attendanceRecords.at(i).getDate().getDateTime() << "," << attendanceRecords.at(i).getCourseID();
        os << "," << attendanceRecords.at(i).getStudentID() << endl;
      }
    }
  }

  if(isEmpty)
  {
    os << "No records" << endl;
  }

}
