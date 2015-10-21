#include "Scheduler.h"
#include <sys/time.h>
#include <iostream>

#ifdef _PC
Millis millis;
#endif

// ------ CLASS SCHEDULER ----------

Process* Scheduler::addProcess(Process& pr, millis_t m)
{
  pr.callAgain = true;
  pr.tgap = m;
  pr.pct = 0;
  pr.id = ++id_count;

  process_priority_queue.insert(&pr);
  Process* h = process_priority_queue.top();
  //pr is a reference to the process, id_t is also;
	return &pr;
}

bool Scheduler::killProcess(Process* proch) 
{
  id_count = 0;
  proch->callAgain = false;
  return true;
}

void Scheduler::loop()
{
	time = millis();	
  Process* highest_priority_process  = process_priority_queue.top();

  // is it time to call?
  if( highest_priority_process->pct < time)
  {
#ifdef __PC
    process_priority_queue.print();
#endif
    process_priority_queue.pop();

    if(highest_priority_process->callAgain == true)
    {
      highest_priority_process->call();
      highest_priority_process->pct = highest_priority_process->tgap + time;
      process_priority_queue.insert(highest_priority_process);
    }
  }
}

millis_t Scheduler::getTime() {
  return time;
}

// ------------ CLASS PROCESS ---------
bool GreaterPriorityComparator::operator()(const Process* lhs, const Process* rhs){
  return lhs->pct < rhs->pct;
}

#ifdef __PC
std::ostream& operator<<(std::ostream& o, Process* proc){
  o<< "process " << proc->id << " next call time is " << proc->pct <<std::endl;
  return o;
}
#endif
