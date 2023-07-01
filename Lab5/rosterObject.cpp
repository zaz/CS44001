// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <set>
#include <map>
#include <algorithm>
#include <filesystem>  // for proper handling of file paths

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;


class Student{
public:
   Student(string firstName, string lastName):
      firstName_(firstName), lastName_(lastName) {}

   // Move constructor. Not needed; generated automatically.
   // Student(Student && org) noexcept:
   //    firstName_(std::move(org.firstName_)),
   //    lastName_(std::move(org.lastName_)) {}

   // force generation of default copy constructor
   Student(const Student & org) = default;

   string print() const { return firstName_ + ' ' + lastName_; }

   // needed for unique() and for remove()
   friend bool operator== (Student left, Student right) {
      return left.lastName_ == right.lastName_ &&
         left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator< (Student left, Student right) {
      return left.lastName_ < right.lastName_ ||
         (left.lastName_ == right.lastName_ &&
          left.firstName_ < right.firstName_);
   }

   void addCourse(string courseName) { courses_.insert(courseName); }

   string getCourses() const {
      string courses;
      for (const auto& str : courses_)
         courses += " " + str;
      return courses;
   }
private:
   string firstName_;
   string lastName_;
   std::set<string> courses_;
};

void readRoster(std::set<Student>& studentCourses,
                string filePath,
                string courseName) {
   ifstream course(filePath);
   string first, last;
   while(course >> first >> last)
      // FIXME: access element of set
      studentCourses[Student(first, last)].addCourse(courseName);
   course.close();
}

// printing a list out
void printRoster(const list<Student>& roster) {
   for(const auto& student : roster)
      cout << student.print() << endl;
}

string getCourseNameFromPath(const std::filesystem::path& path) {
   return path.filename().replace_extension().string();
}

int main(int argc, char* argv[]) {
   if (argc <= 1) { cout << "usage: " << argv[0]
      << " list of courses, dropouts last" << endl; exit(1); }

   vector<string> paths;
   vector<string> courses;
   for (int i = 1; i < argc-1; ++i)
      courses.push_back(getCourseNameFromPath(argv[i]));

   for (const auto& course : courses)
      std::cerr << course << endl;

   // XXX: should I use enums instead of strings?
   std::set<Student> studentCourses;

   for(int i=0; i < argc-2; ++i) {
      list<Student> roster;
      readRoster(studentCourses, argv[i+1], courses[i]);
      std::cerr << '\n' << argv[i+1] << ' ' << courses[i] << '\n';
   }

   for (const auto& [student, courses] : studentCourses)
      std::cerr << student.print() << ' ' << student.getCourses() << '\n';
}
