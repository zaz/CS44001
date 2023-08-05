// Prototype Scheduler
// Mikhail Nesterenko
// Modified by Zaz Brown

#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
using std::cin; using std::cout; using std::endl; using std::string;

const unsigned int initialProcesses = 23;

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

   // method required for prototype pattern
   Process* clone() {return new Process(*this);}

   friend std::ostream& operator<<(std::ostream& os, const Process& process) {
      if (process.n_ < 10)
         os << ' ';
      os << process.n_;
      return os;
   }

   // copy constructor must increment n_
   Process(const Process& p) : n_(nProcesses) {state_=p.state_; ++nProcesses;}

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

// Process constructor must increment n_
Process::Process() : n_(nProcesses) {state_=Ready::instance(); ++nProcesses;}

// handles/behaviors
void  Process::suspend() {state_-> suspend(this);}
void Process::dispatch() {state_->dispatch(this);}
void    Process::block() {state_->   block(this);}
void  Process::unblock() {state_-> unblock(this);}
void     Process::exit() {state_->    exit(this);}
string Process::report() {return state_->report();}

void runAProcess(Process& prototypeProcess) {
   Process* myProcess = prototypeProcess.clone();
   cout << myProcess->name() << " is " << myProcess->report() << endl;

   while(myProcess->report() != "dead"){
      cout << "What would you like "
           << myProcess->name()
           << " to do? Dispatch, suspend, block, unblock, or exit? [d/s/b/u/x] ";
      char action; cin >> action;
      if (action == 'd')
         myProcess->dispatch();
      else if (action == 's')
         myProcess->suspend();
      else if (action == 'b')
         myProcess->block();
      else if (action == 'u')
         myProcess->unblock();
      else if (action == 'x') {
         myProcess->exit();
      } else
         std::cerr << "Invalid action.\n" << std::flush;
      cout << myProcess->name() << " is " << myProcess->report() << endl;
   }
   cout << endl;
}  // this } deletes zork
// and furthers the war on dynamic memory allocation

int main() {
   // create a prototype process, "Process 0"
   Process prototypeProcess;

   // we use deque because it is enumerable, which is useful for printing
   std::deque<Process*> ready;
   // we could use generate_n with back_inserter, but that would be less succinct
   for (unsigned int i = 0; i < initialProcesses; ++i)
      ready.push_back(prototypeProcess.clone());

   Process* running = ready.front();
   ready.pop_front();
   running->dispatch();

   std::deque<Process*> blocked;

   for (int i = 0; i < 20; ++i) {
      cout << "Running: " << *running << endl;

      // XXX QUESTION: why does this print 33 every other element?
      // for (auto i = ready.front(); i != ready.back(); ++i)
      //    cout << *i << ' ';
      // cout << endl;
      //
      // Prints:
      // 2 33  3 33  4 33  5 33  6 33  7 33  8 33  9 33 10 33 11 33 12 33 13 33 14 33 15 33 16 33 17 33 18 33 19 33 20 33 21 33 22 33

      cout << "Ready:   ";
      for (auto process : ready)
         cout << *process << ' ';
      cout << endl;

      cout << "Blocked: ";
      for (auto process : blocked)
         cout << *process << ' ';
      cout << endl;

      // randomly, with 1/3 chance:
      unsigned int action = rand() % 3;
      // move a process from running to blocked
      if (action == 0) {
         cout << "Blocking  " << *running << endl;
         running->block();
         blocked.push_back(running);
         running = ready.front();
         ready.pop_front();
         running->dispatch();
      // move a process from running to ready
      } else if (action == 1) {
         cout << "Suspending " << *running << endl;
         running->suspend();
         ready.push_back(running);
         running = ready.front();
         ready.pop_front();
         running->dispatch();
      // destroy the running process
      } else {
         cout << "Exiting    " << *running << endl;
         delete running;
         running = ready.front();
         ready.pop_front();
         running->dispatch();
      }

      cout << endl;
   }
}
