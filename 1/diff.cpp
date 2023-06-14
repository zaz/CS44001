// finds the location of the first difference between two text files
// Zaz Brown

#include <iostream>
#include <fstream>

void error(std::string message) {
  std::cout << "ERROR: " << message << std::endl;
  exit(1);
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
}
