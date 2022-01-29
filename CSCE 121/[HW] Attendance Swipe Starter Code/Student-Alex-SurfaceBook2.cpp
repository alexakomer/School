#include <iostream>
#include <string>
#include "Student.h"

using std::cout, std::endl, std::string, std::invalid_argument;

//   Student copy constructor
Student::Student(std::string student_id, std::string name)
{
  this->id = student_id;
  this->name = name;
}

string Student::get_id() const
{
  return id;
}

string Student::get_name() const
{
  return name;
}

void Student::addCourse(std::string course_id)
{
  for (size_t i = 0; i < course_ids.size(); i++)
  {
    if (course_ids.at(i) == course_id)
      throw invalid_argument("Class already exists");
  }
  course_ids.push_back(course_id);
}

void Student::listCourses(std::ostream& os) const
{
  if (course_ids.empty())
  {
    os << "Courses for " << id << endl;
    os << "No courses" << endl;
  }
  else
  {
    os << "Courses for " << id << endl;
    for (size_t i = 0; i < course_ids.size(); i++)
      os << course_ids.at(i) << endl;
  }
}
