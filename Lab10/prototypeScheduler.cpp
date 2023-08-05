// Prototype Scheduler
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
   string name() {return "Process " + std::to_string(n_);}
   string report();

   // part of implementation of state pattern
   void changeState(State* state) {state_=state;}
   static unsigned int nProcesses;
private:
   State* state_;
   unsigned int n_;
};

unsigned int Process::nProcesses = 0;

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
   // copying and creation prohibited
   Running(){};
   Running(const Running&){};
   Running& operator=(const Running&){return *this;};
};

class Blocked: public State {
public:
   static State* instance() {
      static State* onlyInstance = new Blocked;
      return onlyInstance;
   }
   void unblock(Process*) override;
   string report() override {return "blocked";}
private:
   // copying and creation prohibited
   Blocked(){};
   Blocked(const Blocked&){};
   Blocked& operator=(const Blocked&){return *this;};
};

class Dead: public State {
public:
   static State* instance() {
      static State* onlyInstance = new Dead;
      return onlyInstance;
   }
   string report() override {return "dead";}
private:
   // copying and creation prohibited
   Dead(){};
   Dead(const Dead&){};
   Dead& operator=(const Dead&){return *this;};
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
Process::Process() : n_(nProcesses) {state_=Ready::instance(); ++nProcesses;}

// handles/behaviors
void  Process::suspend() {state_-> suspend(this);}
void Process::dispatch() {state_->dispatch(this);}
void    Process::block() {state_->   block(this);}
void  Process::unblock() {state_-> unblock(this);}
void     Process::exit() {state_->    exit(this);}
string Process::report() {return state_->report();}

void runAProcess() {
   Process myProcess;
   cout << myProcess.name() << " is " << myProcess.report() << endl;

   while(myProcess.report() != "dead"){
      cout << "What would you like "
           << myProcess.name()
           << " to do? Dispatch, suspend, block, unblock, or exit? [d/s/b/u/x] ";
      char action; cin >> action;
      if (action == 'd')
         myProcess.dispatch();
      else if (action == 's')
         myProcess.suspend();
      else if (action == 'b')
         myProcess.block();
      else if (action == 'u')
         myProcess.unblock();
      else if (action == 'x') {
         myProcess.exit();
      } else
         std::cerr << "Invalid action.\n" << std::flush;
      cout << myProcess.name() << " is " << myProcess.report() << endl;
   }
   cout << endl;
}  // this } deletes zork
// and furthers the war on dynamic memory allocation

int main() {
   runAProcess();

   char answer = 'y';
   // loop, promping user if they want to run another process
   while (answer == 'y') {
      cout << "Would you like to run another process? [y/N] ";
      cin >> answer;
      if (answer != 'y' && answer != 'Y')
         break;
      runAProcess();
   }
}
