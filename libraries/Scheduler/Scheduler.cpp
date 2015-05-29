#include "Scheduler.h"

// ------ CLASS SCHEDULER ----------
Scheduler::Scheduler() 
{	
}

Scheduler::~Scheduler()
{
	// this class manages mem in the free store but no need to bother deleting it since this class will never be destroied
}

ProcessHandle Scheduler::addProcess(const Process& pr, millis_t m)
{
  pr.callAgain = true;
  pr.tgap = m;

  ppq.insert(&pr);
  //pr is a reference to the process, pid_t is also;
	return &pr;
}

bool Scheduler::killProcess(const ProcessHandle h) 
{
  h->callAgain = false;
}

void Scheduler::loop()
{
beg:
	// keep a base "call clock" of a 100hr
	// Lower frequency calls +++ count of a base 
	time = millis();	

  // pop the process with the highest priority
  ProcessHandle h  = ppq.top();

  // is it time to call?
  if( h->pct > time)
  {
    ppq.pop();

    if(h->callAgain == true)
    {
      h->call();
      h->pct = h->tgap + time;
      ppq.insert(h);
    }
  }
  goto beg;
}


// ------------ CLASS PROCESS ---------
bool Process::operator>(const Process& rhs) const
{
  bool b;
  if(pct > rhs.pct) b = true;
  else b = (pid > rhs.pid);
  return b;
}

bool Process::operator==(const Process& rhs) const
{
  return pid == rhs.pid;
}
