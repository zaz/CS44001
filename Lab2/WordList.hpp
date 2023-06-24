#ifndef WORDLIST_H_
#define WORDLIST_H_

#include <string>
#include <set>

using string = std::string;

class WordList{
public:
    WordList() : size_(0) {};
    // add copy constructor, destructor, overloaded assignment

    // implement comparison as friend
    friend bool equal(const WordList&, const WordList&);

    std::set<string> uniqueWords();
    void addWord(const string &);
    void print();
private:
    std::multiset<string> wordCounts_;
    int size_;
};

#endif // WORDLIST_H_
