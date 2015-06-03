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

  /*
  ppq.print();
  Serial.print(" ");
  Serial.print(time);
  Serial.print("\n");
  */
  // is it time to call?
  if( h->pct < time)
  {
    //Serial.print("pop");
    //ppq.print();
    ppq.pop();

    if(h->callAgain == true)
    {
      //Serial.print("call ");
      h->pct = h->tgap + time;
      //Serial.print(h->pct);
      h->call();
      ppq.insert(h);
      Serial.print("\n");
    }
  }
  goto beg;
}


// ------------ CLASS PROCESS ---------
/*
bool Process::operator<(const Process& rhs) const
{
  bool b;
  if(pct < rhs.pct) b = true;
  else b = (pid < rhs.pid);
  return b;
}
*/

bool Process::operator<(const Process& rhs) const
{
  return pct < rhs.pct;
}

bool Process::operator==(const Process& rhs) const
{
  return pid == rhs.pid;
}
