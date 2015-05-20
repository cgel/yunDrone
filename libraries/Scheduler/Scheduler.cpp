#include <Scheduler.h> 

// CLASS SCHEDULER
Scheduler::Scheduler(): 
{	
}

Scheduler::~Scheduler()
{
	// this class manages mem in the free store but no need to bother deleting it since this class will never be destroied
}

pid_t Scheduler::addProcess(Process& pr, const Frequency freq)
{
  ppq->insert(pr);

  //pr is a reference to the process, pid_t is also;
	return pr;
}

void Scheduler::killProcess(const pid_t& pid)
{
	processes[pid.first].erase(pid.second);
  // there is a chanse that ppq might return +1 possible values. see multiset doc
  std::pair<auto, auto> rng = ppq.equal_range(pid);
  for(;rng.first !=rng.second; ++(rng.first) )
  {
    if(rng.first == pid)
    {
      ppq.remove(rng.first);
      println("pid deleted");
    }
  }
}

void Scheduler::loop()
{
beg:
	// keep a base "call clock" of a 100hr
	// Lower frequency calls +++ count of a base 
	time = millis();	

  // high priority process
  auto iter  = ppq.cbegin();
  auto hpp  = *iter;

  if( ->pct > time)
  {
    hpp->call();
    ppq.remove(iter);
    hpp->pct = hpp->tgap + time;
    ppq.insert(hpp);
  }

  goto beg;
}
