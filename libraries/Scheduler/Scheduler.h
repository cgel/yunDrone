#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include <StandardCplusplus.h>
#include <list>
#include <set>
#include <iterator>
#include <iterator>
#include <Arduino.h>

typedef unsigned long millis_t;

enum Frequency { _100hr, _50hr, _10hr, _1hr, _0p1hr};

// derive from this class to create a usable process
class Process {
  public:
  Process() {};
  //virtual ~Process() = 0;

  virtual void call(); //The main function that must be defined when deriving this class.

  operator>(Process& rhs); // has less priority

  private:
  millis_t ptc;  // the perfect time to call update
  millis_t tgap;  // desired time gap between calls ** function of the frequency **
  millis_t tburst;  // estimated call duration
};

// pid here means process identifier
typedef Process& pid_t;

class Scheduler {
	// pid here means process identifier
	public:
	Scheduler();	
	~Scheduler();

	pid_t addProcess(Process& pr, const Frequency freq);
	void killProcess(const pid_t& pid);

	void loop();

	private:
	std::multiset<pid_t, std::greater> ppq; // processes priority queue

	millis_t time;
	millis_t last_call_time;
};

#endif
