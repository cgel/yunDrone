#include <Scheduler.h> 

// ------ CLASS SCHEDULER ----------
Scheduler::Scheduler() 
{	
}

Scheduler::~Scheduler()
{
	// this class manages mem in the free store but no need to bother deleting it since this class will never be destroied
}

pid_t Scheduler::addProcess(Process& pr, const Frequency freq)
{
  ppq.insert(&pr);

  //pr is a reference to the process, pid_t is also;
	return &pr;
}

bool Scheduler::killProcess(pid_t pid)
{
  // there is a chanse that ppq might return +1 possible values. see multiset doc
  //std::pair<ppq_iter_t, ppq_iter_t> rng = ppq.equal_range(pid);
  auto rng = ppq.equal_range(pid);
  for(;rng.first !=rng.second; ++(rng.first) )
  {
    if( *(rng.first) == pid)
    {
      ppq.erase(rng.first);
      cout << "pid deleted" << endl;
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
  ppq_iter_t iter  = ppq.begin();

  pid_t hpp  = *iter;

  if( hpp->pct > time)
  {
    hpp->call();
    ppq.erase(iter);
    hpp->pct = hpp->tgap + time;
    ppq.insert(hpp);
  }

  goto beg;
}


// ------------ CLASS PROCESS ---------
bool Process::operator>(const Process& rhs)
{
  return pct > rhs.pct;
}

bool Process::operator==(const Process& rhs)
{
  return n == rhs.n;
}


// ------------- CLASS PID_T -------------------
pid_t::pid_t() {}

pid_t::pid_t(Process* p)
{
  proc = p;
}

Process& pid_t::operator*()
{
  return *proc;
}

Process* pid_t::operator->()
{
  return proc;
}

bool pid_t::operator==(const pid_t& rhs)
{
  return proc->n == rhs.proc->n;
}

bool pid_t::operator<(const pid_t& rhs)
{
  return proc->pct > rhs.proc->pct;
}

