#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include <list>
#include <iterator>
#include <StandardCplusplus.h>
#include <iterator>

enum Frequency { _100hr, _50hr, _10hr, _1hr, _0p1hr};

// derive from this class to create a usable process
class Process {
	public:
	Process();
	virtual ~Process();

	virtual void update(); //The main function that must be defined when deriving this class.

	private:
};

// pid here means process identifier
class pid_t {
	public:
	pid_t(Frequency f, std::list<Process*>::iterator s): first(f), second(s) {};
	Frequency first;
	std::list<Process*>::iterator second;
};

class Scheduler {
	// pid here means process identifier
	public:
	Scheduler();	
	~Scheduler();

	pid_t addProcess(Process * pr, const Frequency freq);
	void killProcess(const pid_t& pid);

	void update();

	private:

	// processes is an array of vector of iterators (the vectors gup the iteratos of the same freq)
	std::list<Process*> processes[5];

	short int _0p1hr_count;
	short int _1hr_count;
	short int _10hr_count;
	short int _50hr_count;
	unsigned long time;
	unsigned long last_call_time;
};


#endif
