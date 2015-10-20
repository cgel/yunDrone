#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#define _PC
#ifndef _PC
#include <Arduino.h>
#else
#include "fake_millis.h" 
#endif

#include "Heap.h"

typedef unsigned long millis_t;

typedef short unsigned int id_t;
// derive from this class to create a usable process
class Process {
  friend class Scheduler;

 public:
  Process() {};
  virtual ~Process() {};

  virtual void call() = 0;  // The main function that must be defined when deriving
                        // this class.

  bool priorityCompare(const Process& rhs) const;

  bool operator<(const Process& rhs) const;   // has less priority
  bool operator==(const Process& rhs) const;  // compare is two processes are
                                              // the same. Done comparing the
                                              // call function pointers

 private:
  // private: // use protected and friends
  id_t id;
  millis_t pct;   // the perfect call time update
  millis_t tgap;  // desired time gap between calls ** function of the frequency
                  // **
  millis_t tburst;  // estimated call duration

  bool callAgain;
};

// id here means process identifier
typedef Process* ProcessHandle;

struct ProcessHandleComp {
  bool operator()(const ProcessHandle lhs, const ProcessHandle rhs) {
    return *lhs < *rhs;
  }
};

class Scheduler {
  // id here means process identifier
 public:
Scheduler():id_count(0) {};
  ProcessHandle addProcess(Process& pr, millis_t);
  bool killProcess(ProcessHandle proc);

  void loop();

  millis_t getTime();

 private:
  millis_t time;
  Heap<ProcessHandle, ProcessHandleComp> ppq;  // processes priority queue
  id_t id_count;

  millis_t last_call_time;
};

#endif
