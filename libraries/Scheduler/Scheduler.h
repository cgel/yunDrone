#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include <Arduino.h>
#include "Heap.h"


using namespace std;

typedef unsigned long millis_t;


typedef short unsigned int pid_t;
// derive from this class to create a usable process
class Process {
  friend class Scheduler;
  public:
  Process() {};
  //virtual ~Process() = 0;

  virtual void call(); //The main function that must be defined when deriving this class.

  bool priorityCompare( const Process& rhs) const;

  bool operator<(const Process& rhs) const; // has less priority
  bool operator==(const Process& rhs) const; // compare is two processes are the same. Done comparing the call function pointers 

  private:
  //private: // use protected and friends
  pid_t pid;
  millis_t pct;  // the perfect call time update
  millis_t tgap;  // desired time gap between calls ** function of the frequency **
  millis_t tburst;  // estimated call duration


  bool callAgain;
};



// pid here means process identifier
typedef Process* ProcessHandle;

struct ProcessHandleComp {
  bool operator()(const ProcessHandle lhs, const ProcessHandle rhs)
  {
    return  *lhs < *rhs;
  }
};

class Scheduler {
	// pid here means process identifier
	public:
	ProcessHandle addProcess(Process& pr, millis_t);
	bool killProcess(ProcessHandle proc);

	void loop();

  millis_t getTime();

	private:
	millis_t time;
  Heap<ProcessHandle, ProcessHandleComp> ppq; // processes priority queue
  pid_t pid_count;

	millis_t last_call_time;
};


#endif
