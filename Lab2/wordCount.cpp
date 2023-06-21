//
// Counts how many times each word occurs in a file.
// Words are separated by whitespace or punctuation. Case is ignored.
//
// Zaz Brown
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <set>
#include <regex>

void error(std::string message) {
  std::cout << "ERROR: " << message << std::endl;
  // XXX: Does exit call destructors on everything in main?
  exit(1);
}

// convert each letter in a string to lower case
void downcase(std::string& line) {
  std::transform(line.begin(), line.end(), line.begin(),
                  [](unsigned char c){ return std::tolower(c); } );
}

int main(int argc, char* argv[]){
  // throw an error if we are not given one command line arguments
  // XXX: Is it safe to assume argc == argv.size()?
  if (argc != 2) error("You must specify a file to count words in.");

  const std::string file = argv[1];

  // Open the files
  // XXX: Is there a better way than .fail() to check if the file is readable?
  std::ifstream stream(file);
  if (stream.fail()) error("Could not open file " + file);

  std::multiset<std::string> wordCounts;
  std::string line;
  // until we reach the end of one of the files
  while (getline(stream, line)) {
    downcase(line);

    // match words
    std::regex re("\\w+");
    std::sregex_token_iterator match{line.begin(), line.end(), re}, last;

    // store each token from sregex iterator in the multiset
    for (auto& token = *match; match != last; ++match)
      wordCounts.insert(token);
  }

  if (stream.bad()) error("While reading file " + file);

  // TODO: order from rarest to most common
  std::string prevWord = "";
  for ( auto& word : wordCounts ) {
    if (word == prevWord) continue;
    prevWord = word;
    std::cout << wordCounts.count(word) << ' ' << word << '\n';
  }
}
