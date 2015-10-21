#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#define _PC
#ifndef _PC
#include <Arduino.h>
#else
#include "fake_millis.h" 
#endif

#include "Heap.h"

typedef short unsigned int id_t;

// derive from this class to create a usable process
class Process {
  friend class Scheduler;

 public:
  Process() {};
  virtual ~Process() {};

  virtual void call() = 0;  // The main function that must be defined when deriving
                        // this class.

  friend class GreaterPriorityComparator;

#ifdef __PC
  friend std::ostream& operator<<(std::ostream& o, Process* proc);
#endif
  bool operator<(const Process& rhs) const;   // has less priority

 protected: 
  id_t id;
  millis_t pct;   // the perfect call time update
  millis_t tgap;  // desired time gap between calls ** function of the frequency
  millis_t tburst;  // estimated call duration
  bool callAgain;
};

class GreaterPriorityComparator {
  public:
  bool operator()(const Process* lhs, const Process* rhs);
};

#ifdef __PC
std::ostream& operator<<(std::ostream& o, Process* proc);
#endif

class Scheduler {
 public:
  Scheduler():id_count(0) {};
  Process* addProcess(Process& pr, millis_t);
  bool killProcess(Process* proc);

  void loop();

  millis_t getTime();

 private:
  millis_t time;
  Heap<Process*, GreaterPriorityComparator> process_priority_queue;  // processes priority queue
  id_t id_count;

  millis_t last_call_time;
};


#endif
