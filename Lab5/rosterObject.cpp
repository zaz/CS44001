//
// Student roster using associative containers
//
// Zaz Brown
//

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

using std::string;
using std::vector;

// I changed the implementation because adding set<string> courses_ to Student
// would make Student mutable. So we wouldn't easily be able to have a set of
// students.

// I didn't see any place to use std::move that wasn't better handled by passing
// by reference or by the compiler's copy elision. However, I am familiar with
// move sematics, have used them before, and am aware that sometimes data can
// only be moved, not copied, such as with unique_ptr.


class Student : public std::pair<string, string> {
public:
   // constructor
   Student(string firstName, string lastName) :
      std::pair<string, string>(firstName, lastName) {}

   friend std::ostream& operator<<(std::ostream& os, const Student& s) {
      return os << s.first << ' ' << s.second;
   }

   // Compare by last name first.  XXX: Commented out to match the provided test
   // case, which is sorted by first name.
   // friend bool operator<(const Student& left, const Student& right) {
   //    return left.second < right.second ||
   //       (left.second == right.second &&
   //        left.first < right.first);
   // }
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
   std::ifstream course(filePath);
   string first, last;
   while(course >> first >> last)
      studentCourses[Student(first, last)].insert(courseName);
   course.close();
}

string getCourseNameFromPath(string path) {
   // get only the filename, not the whole path, and not the extension
   path = path.substr(path.find_last_of('/') + 1);
   path = path.substr(0, path.find_last_of('.'));
   return path;
}

int main(int argc, char* argv[]) {
   if (argc <= 1) {
      std::cerr << "usage: " << argv[0] << " course.txt... dropouts.txt\n";
      exit(1);
   }

   // "dropouts" is added as a special course
   vector<string> courses;
   for (int i = 1; i < argc; ++i)
      courses.push_back(getCourseNameFromPath(argv[i]));

   // XXX: should I use enums instead of strings?
   std::map<Student, CourseSet> studentCourses;
   for(int i = 0; i < argc-1; ++i)
      readRoster(studentCourses, argv[i+1], courses[i]);

   for (const auto& [student, courseload] : studentCourses) {
      // print "student: courseload" unless the courseload contains the special
      // course "dropouts"
      if (courseload.find(courses.back()) == courseload.end())
         std::cout << student << ':' << courseload << '\n';
   }
}
