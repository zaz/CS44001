#include "WordList.hpp"
#include <iostream>
#include <set>
#include <string>

std::set<std::string> WordList::uniqueWords() {
  return std::set<std::string>(wordCounts_.begin(), wordCounts_.end());
}

void WordList::addWord(const string& word) {
  wordCounts_.insert(word);
}

void WordList::print() {
  for (auto& word : uniqueWords())
    std::cout << wordCounts_.count(word) << ' ' << word << '\n';
}

unsigned int WordList::count(const std::string& word) {
  return wordCounts_.count(word);
}

bool equal(const WordList& w1, const WordList& w2) {
  return w1.wordCounts_ == w2.wordCounts_;
}
