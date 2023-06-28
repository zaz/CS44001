//
// Student roster
//
// Mikhail Nesterenko
// Modified by Zaz Brown
//

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <filesystem>  // for proper handling of file paths

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl; using std::cerr;
using std::move;

// read a file of names into a list of strings
void readRoster(list<string>& roster, string fileName) {
   ifstream course(fileName);
   string first, last;
   // For each line in the file, read the first and second whitespace-separated
   // words into first and last, respectively.
   while(course >> first >> last)
      roster.push_back(first + ' ' + last);
   course.close();
}

// print a list
void printRoster(const list<string>& roster, bool stderr = false) {
   if (stderr) for(const auto& str : roster) cerr << str << '\n';
   else for(const auto& str : roster) cout << str << '\n';
}

// print student entries
void printEntries(const list<list<string>>& entries) {
   for (const auto& student : entries) {
      for (const auto& str : student)
         cout << str;
      cout << '\n';
      }
}

// XXX UGLY. We should use maps instead.
// create studentEntries, a list of lists of: "name: [courses enrolled...]"
list<list<string>> getStudentEntries(const vector<list<string>>& courseStudents,
                                     const list<string>& allStudents,
                                     char* argv[]) {
   list<list<string>> studentEntries;
   for (auto& student : allStudents) {
      list<string> entry;
      entry.push_back(student + ":");
      for (auto& lst : courseStudents) {
         if (std::find(lst.begin(), lst.end(), student) != lst.end()) {
            std::filesystem::path csI = argv[&lst - &courseStudents[0] + 1];
            // get only the filename, not the whole path, and not the extension
            csI = csI.filename();
            csI.replace_extension();
            entry.push_back(" " + string(csI));
         }
      }
      studentEntries.push_back(move(entry));
   }
   return studentEntries;
}

int main(int argc, char* argv[]) {
   if (argc <= 1) {
      cerr << "usage: " << argv[0]
      << " list of courses, dropouts last"
      << endl;
      exit(1);
   }

   // vector of courses of students
   vector<list<string>> courseStudents;
   for (int i=1; i < argc-1; ++i) {
      list<string> roster;
      readRoster(roster, argv[i]);
      // roster now contains a list of students in course argv[i]
      cerr << "\n\n" << argv[i] << "\n";
      printRoster(roster, true);
      courseStudents.push_back(move(roster));
   }

   // reading in dropouts
   list<string> dropouts;
   readRoster(dropouts, argv[argc-1]);
   cerr << "\n\n dropouts \n";
   printRoster(dropouts, true);

   // master list of students
   list<string> allStudents;
   for (const auto& lst : courseStudents)
      // copy list instead of splicing:
      allStudents.insert(allStudents.end(), lst.begin(), lst.end());

   auto studentEntries = getStudentEntries(courseStudents, allStudents, argv);

   cout << "All students\nfirst name last name: courses enrolled";
   printEntries(studentEntries);

   // sorting master list
   allStudents.sort();
   cerr << "\n\n all students sorted \n";
   printRoster(allStudents, true);

   // eliminating duplicates
   allStudents.unique();
   cerr << "\n\n all students, duplicates removed \n";
   printRoster(allStudents, true);

   // removing individual dropouts
   for (const auto& str : dropouts)
      allStudents.remove(str);

   cout << "All students, dropouts removed and sorted\n";
   cout << "first name last name:  courses enrolled\n";
   printRoster(allStudents);
}
