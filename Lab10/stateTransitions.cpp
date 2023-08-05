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
   void block();
   void unblock();
   void exit();
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
   virtual void  suspend(Process*) { std::cerr << "Invalid action.\n"; }
   virtual void dispatch(Process*) { std::cerr << "Invalid action.\n"; }
   virtual void    block(Process*) { std::cerr << "Invalid action.\n"; }
   virtual void  unblock(Process*) { std::cerr << "Invalid action.\n"; }
   virtual void     exit(Process*) { std::cerr << "Invalid action.\n"; }

   virtual string report() = 0;
   void changeState(Process* c, State* s) {
      c->changeState(s);
   }
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

class Running: public State {
public:
   static State* instance() {
      static State* onlyInstance = new Running;
      return onlyInstance;
   }
   void suspend(Process*) override;
   void   block(Process*) override;
   void    exit(Process*) override;
   string report() override {return "running";}
private:
   // here and elsewhere should be stated private constructor/assignment
   // to correctly implement singleton, skipped to simplify code
};

class Blocked: public State {
public:
   static State* instance() {
      static State* onlyInstance = new Blocked;
      return onlyInstance;
   }
   void unblock(Process*) override;
   string report() override {return "blocked";}
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

void Blocked::unblock(Process *c) {
   changeState(c, Ready::instance());
}

void Ready::dispatch(Process *c) {
   changeState(c, Running::instance());
}

void Running::suspend(Process *c) {
   changeState(c, Ready::instance());
}

void Running::block(Process *c) {
   changeState(c, Blocked::instance());
}

void Running::exit(Process *c) {
   changeState(c, Dead::instance());
}

// Process member functions
Process::Process() {state_=Ready::instance();}

// handles/behaviors
void  Process::suspend() {state_-> suspend(this);}
void Process::dispatch() {state_->dispatch(this);}
void    Process::block() {state_->   block(this);}
void  Process::unblock() {state_-> unblock(this);}
void     Process::exit() {state_->    exit(this);}
string Process::report() {return state_->report();}

int main() {
   {
      Process zork;
      cout << "Zork is " << zork.report() << endl;

      while(zork.report() != "dead"){
         cout << "What would you like Zork to do? Dispatch, suspend, block, unblock, or exit? [d/s/b/u/x] ";
         char action; cin >> action;
         if (action == 'd')
            zork.dispatch();
         else if (action == 's')
            zork.suspend();
         else if (action == 'b')
            zork.block();
         else if (action == 'u')
            zork.unblock();
         else if (action == 'x') {
            zork.exit();
         } else
            std::cerr << "Invalid action.\n" << std::flush;
         cout << "Zork is " << zork.report() << endl;
      }
   }  // this } deletes zork
   // and furthers the war on dynamic memory allocation
}
