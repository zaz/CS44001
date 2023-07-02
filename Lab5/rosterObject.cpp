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
#include <filesystem>  // for proper handling of file paths

using std::string;
using std::vector;

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

string getCourseNameFromPath(const std::filesystem::path& path) {
   return path.filename().replace_extension().string();
}

int main(int argc, char* argv[]) {
   if (argc <= 1) {
      std::cerr << "usage: " << argv[0] << " course.txt... dropouts.txt\n";
      exit(1);
   }

   vector<string> courses;
   for (int i = 1; i < argc-1; ++i)
      courses.push_back(getCourseNameFromPath(argv[i]));

   // XXX: should I use enums instead of strings?
   std::map<Student, CourseSet> studentCourses;

   for(int i=0; i < argc-2; ++i)
      readRoster(studentCourses, argv[i+1], courses[i]);

   for (const auto& [student, courses] : studentCourses)
      std::cout << student << ':' << courses << '\n';
}
