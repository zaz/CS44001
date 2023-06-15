//
// Finds the location of the first difference between two text files.
// Returns 0 if they are the same, 1 if they differ, 2 if there is an error.
//
// Zaz Brown
//

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

  const std::string file1 = argv[1];
  const std::string file2 = argv[2];

  // calculate the amount of left padding needed for printing the filenames
  const int filenameLengthDifference = file2.length() - file1.length();
  const auto file1Padding =
    std::string(std::max(0,  filenameLengthDifference), ' ');
  const auto file2Padding =
    std::string(std::max(0, -filenameLengthDifference), ' ');

  // filename prefixes for later printing in a pretty way. e.g.:
  //          file.txt:
  // modified_file.txt:
  const auto file1Prefix = file1Padding + file1 + ": ";
  const auto file2Prefix = file2Padding + file2 + ": ";
  //assert(file1Prefix.length() == file2Prefix.length());

  // Open the files
  // XXX: Is there a better way than .fail() to check if the file is readable?
  std::ifstream stream1(file1);
  if (stream1.fail()) error("Could not open file " + file1);
  std::ifstream stream2(file2);
  if (stream2.fail()) error("Could not open file " + file2);

  std::string lineFrom1;
  std::string lineFrom2;
  int line_number = 0;
  // until we reach the end of one of the files
  while (!stream1.eof() && !stream2.eof()) {
    getline(stream1, lineFrom1);
    getline(stream2, lineFrom2);
    ++line_number;
    if (lineFrom1 != lineFrom2) break;
  }

  if (stream1.eof() && stream2.eof()) {
    // we reached the end of both files without finding a difference!
    return 0;
  }

  const auto prefix1 = file1Prefix + std::to_string(line_number) + ": ";
  std::cout << prefix1 << lineFrom1 << std::endl;
  std::cout << file2Prefix << line_number << ": " << lineFrom2 << std::endl;

  const int minLineLength = std::min(lineFrom1.length(), lineFrom2.length());
  int i = 0;
  while (i < minLineLength) {
    if (lineFrom1[i] != lineFrom2[i]) break;
    ++i;
  }
  // print a ^ under the first character that differs
  std::cout << std::string(prefix1.length()+i, ' ') << '^' << std::endl;
  // exit with return code 1 to indicate the files differ
  return 1;

  if (stream1.bad()) error("While reading file " + file1);
  if (stream2.bad()) error("While reading file " + file2);
}
