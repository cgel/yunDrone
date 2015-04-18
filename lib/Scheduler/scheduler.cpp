// CLASS SCHEDULER
Scheduler::Scheduler(): nextPid(0);	
{

}

Scheduler::~Scheduler();
{

}

pid_t Scheduler::addProcess(Process * pr, Frequency freq);
{
	Prcocesses.push_back(pr)
	pr->pid = Processes.end();
}

void Scheduler::killProcess(pid_t pid)
{
	// pid is a iterator of a vector of pointers to processes
	(*pid)->setPid(NULL); // Make the pid of the prosses invalid
	*pid = NULL; // Make the pointer to the process invalid
}

void Scheduler::update();
{

}
