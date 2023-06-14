// finds the location of the first difference between two text files
// Zaz Brown

#include <iostream>
#include <fstream>

void error(std::string message) {
  std::cout << "ERROR: " << message << std::endl;
  // XXX: Does exit call destructors on everything in main?
  exit(2);
}

int main(int argc, char* argv[]){
  // throw an error if we are not given two command line arguments
  // XXX: Is it safe to assume argc == argv.size()?
  if (argc != 3) error("You must specify 2 files to diff");

  std::string file1 = argv[1];
  std::string file2 = argv[2];

  // Open the files
  // XXX: Is there a better way than .fail() to check if the file is readable?
  std::ifstream stream1(file1);
  if (stream1.fail()) error("Could not open file " + file1);
  std::ifstream stream2(file2);
  if (stream2.fail()) error("Could not open file " + file2);

  std::string lineFrom1;
  std::string lineFrom2;
  int line_number = 1;
  // until we reach the end of one of the files
  while (getline(stream1, lineFrom1) && getline(stream2, lineFrom2)) {
    if (lineFrom1 != lineFrom2) {
      std::cout << "file1: " << line_number << ": " << lineFrom1 << std::endl;
      std::cout << "file2: " << line_number << ": " << lineFrom2 << std::endl;

      int minLineLength = std::min(lineFrom1.length(), lineFrom2.length());
      int i = 0;
      while (i < minLineLength) {
        if (lineFrom1[i] != lineFrom2[i]) break;
        ++i;
      }
      // print a ^ under the first character that differs
      std::cout << std::string(10+i, ' ') << '^' << std::endl;
      return 1;
    }
    ++line_number;
  }

  if (stream1.bad()) error("While reading file " + file1);
  if (stream2.bad()) error("While reading file " + file2);
}
