#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "School.h"
#include "AttendanceRecord.h"

using std::string, std::ostream, std::ifstream, std::istringstream, std::endl, std::cout, std::stoi;

// one method is provided to students; students implement all other methods
void School::addStudents(string filename)
{
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    throw std::invalid_argument("addStudents: can't open file");
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string uin;
    getline(ss, uin, ',');
    string name;
    getline(ss, name);
    if (!ss.fail()) {
        Student student(uin, name);
        bool exists = false;
        for (Student s : students) {
            if (s == student) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            students.push_back(student);
        }
    }
  }
}

bool School::isEnrolled(string student_id) const
{
  for (size_t i = 0; i < students.size(); i++)
  {
    if (students.at(i).get_id() == student_id)
      return true;
  }
  return false;
}

void School::listStudents(std::ostream& os) const
{
  if (students.empty())
    os << "No students" << endl;
  else
  {
    for (size_t i = 0; i < students.size(); i++)
    {
      os << students.at(i).get_id() << "," << students.at(i).get_name() << endl;
    }
  }
}

void School::addCourses(string filename)
{
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    throw std::invalid_argument("addCourses: can't open file");
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string id;
    getline(ss, id, ',');
    string startTimeHour;
    getline(ss, startTimeHour, ':');
    string startTimeMin;
    getline(ss, startTimeMin, ',');
    string endTimeHour;
    getline(ss, endTimeHour, ':');
    string endTimeMin;
    getline(ss, endTimeMin, ',');
    string title;
    getline(ss, title);



    if (!ss.fail()) {
        Date start = Date(stoi(startTimeHour), stoi(startTimeMin));
        Date end = Date(stoi(endTimeHour), stoi(endTimeMin));
        Course course(id, title, start, end);
        bool exists = false;
        for (Course c : courses) {
            if (c.getTitle() == course.getTitle())
            {
                exists = true;
                break;
            }
        }
        if (!exists) {
            courses.push_back(course);
        }
    }
  }
}

void School::listCourses(std::ostream& os) const
{
  if (courses.empty())
    os << "No courses" << endl;
  else
  {
    for (size_t i = 0; i < courses.size(); i++)
    {
      os << courses.at(i).getID() << "," << courses.at(i).getStartTime().getTime(false) << ",";
      os << courses.at(i).getEndTime().getTime(false) << "," << courses.at(i).getTitle() << endl;
    }
  }
}

unsigned int School::addAttendanceData(string filename)
{
  unsigned int invalid = 0;
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    throw std::invalid_argument("addAttendanceData: can't open file");
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string year;
    getline(ss, year, '-');
    string month;
    getline(ss, month, '-');
    string day;
    getline(ss, day, ' ');
    string hour;
    getline(ss, hour, ':');
    string min;
    getline(ss, min, ':');
    string sec;
    getline(ss, sec, ',');
    string course_id;
    getline(ss, course_id, ',');
    string student_id;;
    getline(ss, student_id);

    if (!ss.fail()) {
        Date date = Date(stoi(year), stoi(month), stoi(day), stoi(hour), stoi(min), stoi(sec));
        bool studentExists = false;
        bool courseExists = false;

        for (size_t i = 0; i < students.size(); i++)
        {
          if (student_id == students.at(i).get_id())
          {
            studentExists = true;
            break;
          }
        }

        size_t courseIndex = -1;

        for (size_t i = 0; i < courses.size(); i++)
        {
          if (courses.at(i).getID() == course_id)
            {
                courseExists = true;
                courseIndex = i;
                break;
            }
        }

        if (!date.isValid() || !studentExists || !courseExists)
          invalid++;
        else
        {
          AttendanceRecord attnRcrd(course_id, student_id, date);
          courses.at(courseIndex).addAttendanceRecord(attnRcrd);
        }

    }
  }
  return invalid;
}

void School::outputCourseAttendance(std::ostream& os, std::string course_id) const
{
  bool valid = false;
  size_t courseIndex = -1;
  for (size_t i = 0; i < courses.size(); i++)
  {
    if (courses.at(i).getID() == course_id)
    {
      valid = true;
      courseIndex = i;
    }
  }
  if (!valid)
    throw std::invalid_argument("Course does not exist.");
  else
    courses.at(courseIndex).outputAttendance(os);
}

void School::outputStudentAttendance(std::ostream& os, std::string student_id, std::string course_id) const
{
  bool validCourse = false;
  bool validStudent = false;
  size_t studentIndex = -1;
  size_t courseIndex = -1;

  for (size_t i = 0; i < courses.size(); i++)
  {
    if (courses.at(i).getID() == course_id)
    {
      validCourse = true;
      courseIndex = i;
    }
  }

  for (size_t i = 0; i < students.size(); i++)
  {
    if (students.at(i).get_id() == student_id)
    {
      validStudent = true;
      studentIndex = i;
    }
  }

  if (!validCourse || !validStudent)
    throw std::invalid_argument("Course or student does not exist.");
  else
    courses.at(courseIndex).outputAttendance(os, student_id);
}
