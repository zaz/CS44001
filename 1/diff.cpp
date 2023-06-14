// finds the location of the first difference between two text files
// Zaz Brown

#include <iostream>

int main(int argc, char* argv[]){
  // throw an error if we are not given two command line arguments
  // XXX: Is it safe to assume argc == argv.size()?
  if (argc != 3) {
    std::cout << "ERROR: You must specify 2 files to diff" << std::endl;
    return 1;
  }
}
