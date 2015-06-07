#include "Scheduler.h"

// ------ CLASS SCHEDULER ----------

ProcessHandle Scheduler::addProcess(Process& pr, millis_t m)
{
  pr.callAgain = true;
  pr.tgap = m;
  pr.pct = 0;
  pr.pid = ++pid_count;

  ppq.insert(&pr);
  ProcessHandle h = ppq.top();
  //pr is a reference to the process, pid_t is also;
	return &pr;
}

bool Scheduler::killProcess(ProcessHandle proch) 
{
  pid_count = 0;
  proch->callAgain = false;
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
  return pct < rhs.pct;
}

bool Process::operator==(const Process& rhs) const
{
  return pid == rhs.pid;
}
