#include "Scheduler.h"
#include <sys/time.h>
#include <iostream>

#ifdef _PC
Millis millis;
#endif

// ------ CLASS SCHEDULER ----------

ProcessHandle Scheduler::addProcess(Process& pr, millis_t m)
{
  pr.callAgain = true;
  pr.tgap = m;
  pr.pct = 0;
  pr.id = ++id_count;

  ppq.insert(&pr);
  ProcessHandle h = ppq.top();
  //pr is a reference to the process, id_t is also;
	return &pr;
}

bool Scheduler::killProcess(ProcessHandle proch) 
{
  id_count = 0;
  proch->callAgain = false;
  return true;
}

void Scheduler::loop()
{
beg:
	// keep a base "call clock" of a 100hr
	// Lower frequency calls +++ count of a base 
	time = millis();	

  // find the process with the highest priority
  ProcessHandle h  = ppq.top();

  // is it time to call?
  if( h->pct < time)
  {
    //Serial.print("pop");
    //ppq.print();
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

millis_t Scheduler::getTime() {
  return time;
}

// ------------ CLASS PROCESS ---------

bool Process::operator<(const Process& rhs) const
{
  std::cout << pct << " -- " << rhs.pct << std::endl;
  return pct < rhs.pct;
}

bool Process::operator==(const Process& rhs) const
{
  return id == rhs.id;
}
