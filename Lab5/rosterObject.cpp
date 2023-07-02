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

class Student : public std::pair<string, string> {
public:
   // constructor
   Student(string firstName, string lastName) :
      std::pair<string, string>(firstName, lastName) {}

   friend std::ostream& operator<<(std::ostream& os, const Student& s) {
      return os << s.first << ' ' << s.second;
   }

   friend bool operator<(const Student& left, const Student& right) {
      return left.second < right.second ||
         (left.second == right.second &&
          left.first < right.first);
   }
};

class CourseSet : public std::set<string> {
   friend std::ostream& operator<<(std::ostream& os, const CourseSet& cs) {
      for (const auto& course : cs)
         os << ' ' << course;
      return os;
   }
};


void readRoster(std::map<Student, CourseSet>& studentCourses,
                string filePath,
                string courseName) {
   ifstream course(filePath);
   string first, last;
   while(course >> first >> last)
      // FIXME: access element of set
      studentCourses[Student(first, last)].insert(courseName);
   course.close();
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
   std::map<Student, CourseSet> studentCourses;

   for(int i=0; i < argc-2; ++i) {
      readRoster(studentCourses, argv[i+1], courses[i]);
      std::cerr << '\n' << argv[i+1] << ' ' << courses[i] << '\n';
   }

   for (const auto& [student, courses] : studentCourses)
      std::cerr << student << courses << '\n';
}
