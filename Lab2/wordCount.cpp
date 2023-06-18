//
// Counts how many times each word occurs in a file.
// Words are separated by whitespace or punctuation. TODO: Case is ignored.
//
// Zaz Brown
//

#include <iostream>
#include <fstream>
#include <set>
// #include <cstring>  // TODO

void error(std::string message) {
  std::cout << "ERROR: " << message << std::endl;
  // XXX: Does exit call destructors on everything in main?
  exit(1);
}

int main(int argc, char* argv[]){
  // throw an error if we are not given two command line arguments
  // XXX: Is it safe to assume argc == argv.size()?
  if (argc != 1) error("You must specify a file to count words in.");

  const std::string file = argv[1];

  // Open the files
  // XXX: Is there a better way than .fail() to check if the file is readable?
  std::ifstream stream(file);
  if (stream.fail()) error("Could not open file " + file);

  // create a bag

  std::multiset<std::string> wordCounts;
  std::string line;
  // until we reach the end of one of the files
  while (getline(stream, line)) {
    // TODO: downcase
      // TODO: turn line into C string ?
      // XXX: Why are C strings still used? My understanding was a string is the
      //      same, just that it automatically handles memory allocation and has
      //      some nice helper functions.
    // TODO: split into words

    // TODO: add words to bag
  }

  // TODO: output word counts

  if (stream.bad()) error("While reading file " + file);
}
