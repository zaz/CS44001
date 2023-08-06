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

   cout << "Press RETURN to step through the simulation.\n\n" << std::flush;

   unsigned int action;
   while (true) {
      if (running == nullptr)
         cout << "Running: " << endl;
      else
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

      if (running == nullptr && ready.size() == 0 && blocked.size() == 0)
         break;

      std::cin.get();

      if (running != nullptr) {
         // randomly, with 1/3 chance:
         action = rand() % 3;
         // move a process from running to blocked
         if (action == 0) {
            cout << "Block   " << *running << endl;
            running->block();
            blocked.push_back(running);
         // move a process from running to ready
         // note that if there are no ready processes, this is a no-op
         // (when combined with the code in if (read.size > 0) { ... })
         } else if (action == 1) {
            cout << "Suspend " << *running << endl;
            running->suspend();
            ready.push_back(running);
         // destroy the running process
         } else {
            cout << "Exit    " << *running << endl;
            delete running;
         }
      }
      running = nullptr;
      if (ready.size() > 0) {
         running = ready.front();
         ready.pop_front();
         running->dispatch();
      }

      // with 10% chance, unblock the next process in blocked queue
      if (blocked.size() > 0 && rand() % 5 == 0) {
         cout << "Unblock " << *blocked.front() << endl;
         blocked.front()->unblock();
         ready.push_back(blocked.front());
         blocked.pop_front();
      }

      cout << endl;
   }
}
