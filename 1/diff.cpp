// finds the location of the first difference between two text files
// Zaz Brown

#include <iostream>
#include <fstream>

int main(int argc, char* argv[]){
  // throw an error if we are not given two command line arguments
  // XXX: Is it safe to assume argc == argv.size()?
  if (argc != 3) {
    std::cout << "ERROR: You must specify 2 files to diff" << std::endl;
    return 1;
  }

  std::string file1 = argv[1];
  std::string file2 = argv[2];

  std::ifstream stream1(file1);
  // XXX: Is there a better way to check if the file is readable?
  if(stream1.fail()){
    std::cout << "ERROR: Could not open file " << file1 << std::endl;
    return 1;
  }

  std::ifstream stream2(file2);
  if(stream2.fail()){
    std::cout << "ERROR: Could not open file " << file2 << std::endl;
    return 1;
  }
}
