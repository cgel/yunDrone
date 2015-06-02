#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include <Arduino.h>
#include "Heap.h"


using namespace std;

typedef unsigned long millis_t;


// derive from this class to create a usable process
class Process {
  friend class Scheduler;
  public:
  Process() {};
  //virtual ~Process() = 0;

  virtual void call(); //The main function that must be defined when deriving this class.

  bool priorityCompare( const Process& rhs) const;

  bool operator>(const Process& rhs) const; // has less priority
  bool operator==(const Process& rhs) const; // compare is two processes are the same. Done comparing the call function pointers 

  private:
  //private: // use protected and friends
  millis_t pct;  // the perfect call time update
  millis_t tgap;  // desired time gap between calls ** function of the frequency **
  millis_t tburst;  // estimated call duration

  short unsigned int pid;

  bool callAgain;
};



// pid here means process identifier
typedef Process* ProcessHandle;
bool operator>(Process*, Process*);



class Scheduler {
	// pid here means process identifier
	public:
	ProcessHandle addProcess(Process& pr, millis_t);
	bool killProcess(const* Process proc);

	void loop();

	millis_t time;
	private:
  Heap<Process*> ppq; // processes priority queue

	millis_t last_call_time;
};

#endif
