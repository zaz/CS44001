// demonstrates state design pattern
// Mikhail Nesterenko
// Modified by Zaz Brown

#include <iostream>
#include <string>
using std::cin; using std::cout; using std::endl; using std::string;

class State;

// context
class Process {
public:
   Process();

   // behaviors
   void suspend();
   void dispatch();
   string report();

   // part of implementation of state pattern
   void changeState(State* state) {state_=state;}
private:
   State* state_;
};

// absract state
class State {
public:
   // default to printing "Invalid action."
   virtual void suspend(Process*)  { std::cerr << "Invalid action.\n"; }
   virtual void dispatch(Process*) { std::cerr << "Invalid action.\n"; }

   virtual string report() = 0;
   void changeState(Process* c, State* s) {
      c->changeState(s);
   }
};

class Running: public State {
public:
   static State* instance() {
      static State* onlyInstance = new Running;
      return onlyInstance;
   }
   void suspend(Process*) override;
   string report() override {return "running";}
private:
   // here and elsewhere should be stated private constructor/assignment
   // to correctly implement singleton, skipped to simplify code
};


class Ready: public State {
public:
   static State* instance() {
      static State* onlyInstance = new Ready;
      return onlyInstance;
   }
   void dispatch(Process*) override;
   string report() override {return "ready";}
};


class Dead: public State {
public:
   static State* instance() {
      static State* onlyInstance = new Dead;
      return onlyInstance;
   }
   string report() override {return "dead";}
};


// state transitions member functions

void Running::suspend(Process *c) {
   changeState(c, Ready::instance());
}

void Ready::dispatch(Process *c) {
   changeState(c, Running::instance());
}

// Process member functions
Process::Process() {state_=Ready::instance();}

// handles/behaviors
void Process::suspend() {state_->suspend(this);}
void Process::dispatch() {state_->dispatch(this);}
string Process::report() {return state_->report();}

int main() {
   Process zork;
   cout << "Zork is " << zork.report() << endl;

   while(zork.report() != "dead"){
      cout << "What would you like Zork to do? dispatch or suspend? [d/s] ";
      char action; cin >> action;
      if(action == 'd')
         zork.dispatch();
      else
         zork.suspend();
      cout << "Zork is " << zork.report() << endl;
   }


   // demonstrates that two Process
   // may be in two different states
   Process grue;
   cout << "Zork is " << zork.report() << " while "
        << "Grue is " << grue.report() << endl;

}
