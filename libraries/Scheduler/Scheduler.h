#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include <StandardCplusplus.h>
//#include <list>
#include <set>
//#include <iterator>
#include <Arduino.h>


// after debug remove this
#include <serstream>
using namespace std;

typedef unsigned long millis_t;


enum Frequency { _100hr, _50hr, _10hr, _1hr, _0p1hr};

// derive from this class to create a usable process
class Process {
  public:
  Process() {};
  //virtual ~Process() = 0;

  virtual void call(); //The main function that must be defined when deriving this class.

  bool operator>(const Process& rhs) const; // has less priority
  bool operator==(const Process& rhs) const; // compare is two processes are the same. Done comparing the call function pointers 

  //private: // use protected and friends
  millis_t pct;  // the perfect call time update
  millis_t tgap;  // desired time gap between calls ** function of the frequency **
  millis_t tburst;  // estimated call duration
  short unsigned int n;
};




// pid here means process identifier
class  pid_t
{
  public:
  pid_t();
  pid_t(Process*);
  Process& operator*() const;
  Process* operator->() const;
  bool operator==(const pid_t& rhs) const;
  bool operator<(const pid_t& rhs) const;
  Process* proc;
};



typedef std::multiset<pid_t> ppq_t; // processes priority queue

typedef std::multiset<pid_t>::iterator ppq_iter_t; // processes priority queue
//typedef std::multiset<pid_t>::const_iterator ppq_citer_t; // processes priority queue

class Scheduler {
	// pid here means process identifier
	public:
	Scheduler();	
	~Scheduler();

	pid_t addProcess(Process& pr, const Frequency freq);
	bool killProcess(const pid_t pid);

	void loop();

	millis_t time;
	private:
  ppq_t ppq; // processes priority queue

	millis_t last_call_time;
};

#endif
