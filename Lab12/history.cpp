// History
// Mikhail Nesterenko
// Modified by Zaz Brown

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using std::vector; using std::string;
using std::cout; using std::cin; using std::endl;

// receiver
class Document {
public:

   Document(const vector <string> & lines={}): lines_(lines) {}

   // actions
   void insert(int line, const string &str) {
      const unsigned int index = line-1;
      if (index <= lines_.size())
         lines_.insert(lines_.begin() + index, str);
      else
         cout << "line out of range" << endl;
   }

   const string remove(int line) {
      const unsigned int index = line-1;
      string deletedLine="";
      if (index < lines_.size()) {
         deletedLine = lines_[index];
         lines_.erase(lines_.begin() + index);
      } else
         cout << "line out of range" << endl;
      return deletedLine;
   }

   void show() {
      for (unsigned int i = 0; i < lines_.size(); ++i)
         cout << i + 1 << ". " << lines_[i] << endl;
   }

private:
   vector<string> lines_;
};

// abstract command
class Command {
public:
   Command(Document *doc) : doc_(doc) {}
   virtual void execute() = 0;
   virtual void unexecute() = 0;
   virtual ~Command(){}
   virtual string show() const = 0;
protected:
   Document *doc_;
};

// two concrete commands
class InsertCommand : public Command {
public:
   InsertCommand(Document *doc, int line, const string &str):
      Command(doc), line_(line),  str_(str) {}
   void execute() override { doc_->insert(line_, str_);}
   void unexecute() override {doc_->remove(line_);}
   string show() const override {
      return "insert " + std::to_string(line_) + ": " + str_;
   }
private:
   int line_;
   string str_;
};


class EraseCommand : public Command {
public:
   EraseCommand(Document *doc, int line):
      Command(doc), line_(line), str_("") {}
   void execute() override {str_ = doc_->remove(line_);}
   void unexecute() override {doc_->insert(line_, str_);}
   string show() const override {
      return "erase " + std::to_string(line_) + ": " + str_;
   }
private:
   int line_;
   string str_;
};

// client
class DocumentWithHistory {
public:
   DocumentWithHistory(const vector<string> & text={}) : doc_(text) {}

   void insert(int line, string str) {
      Command *com = new InsertCommand(&doc_, line, str);
      com->execute();
      doneCommands_.push(com);
   }

   void erase(int line) {
      Command *com = new EraseCommand(&doc_, line);
      com->execute();
      doneCommands_.push(com);
   }

   void undo() {
      if (doneCommands_.size() != 0) {
         Command *com = doneCommands_.top();
         doneCommands_.pop();
         com->unexecute();
         delete com; // don't forget to delete command
      } else
         std::cerr << "No commands to undo.\n" << std::flush;
   }

   void rollback() {
      while (!doneCommands_.empty()) undo();
   }

   void clearHistory() {
      while (!doneCommands_.empty()) {
         delete doneCommands_.top();
         doneCommands_.pop();
      }
   }

   void show() {doc_.show();}
   void printHistory() const {
      std::stack<Command*> temp = doneCommands_;
      while (!temp.empty()) {
         cout << temp.top()->show() << endl;
         temp.pop();
      }
   }

private:
   Document doc_;
   std::stack<Command*> doneCommands_;
};

// invoker
int main() {
   DocumentWithHistory his({
         "Lorem Ipsum is simply dummy text of the printing and typesetting",
         "industry. Lorem Ipsum has been the industry's standard dummy text",
         "ever since the 1500s, when an unknown printer took a galley of",
         "type and scrambled it to make a type specimen book. It has",
         "survived five centuries."});

   char option;
   do {
      his.show();
      cout << endl;

      cout << "Enter option (i)nsert line, (e)rase line, (u)ndo last command "
           << "(c)heckpoint\n             roll(b)ack (h)istory (r)edo command: ";
      cin >> option;

      int line; string str;
      switch(option) {
      case 'i':
         cout << "line number to insert: ";
         cin >> line;
         cout << "line to insert: ";
         cin.get(); // removes end-of-line character so getline() works correctly
         getline(cin, str);
         his.insert(line, str);
         break;

      case 'e':
         cout << "line number to remove: ";
         cin >> line;
         his.erase(line);
         break;

      case 'u':
         his.undo();
         break;

      case 'c':
         his.clearHistory();
         break;

      case 'b':
         his.rollback();
         break;

      case 'h':
         his.printHistory();
         break;

      case 'r':
         std::cerr << "Not implemented.\n" << std::flush;
         break;
      }

   } while (option == 'i' || option == 'e' || option == 'u' || option == 'c'
                          || option == 'b' || option == 'h' || option == 'r');
}
