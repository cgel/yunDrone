// CLASS SCHEDULER
Scheduler::Scheduler(): nextPid(0);	
{	
	_50hr_count = 1;
	_10hr_count = 2;
	_1hr_count = 3; 
	_0.1hr_count = 4;
}

Scheduler::~Scheduler()
{

}

pid_t Scheduler::addProcess(Process * pr, Frequency freq)
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

void Scheduler::update()
{
	// keep a base "call clock" of a 100hr
	// Lower frequency calls +++ count of a base 
	time = millis();	
	if (time - last_call_time() > 10) // 10 milliseconds 
	{
		last_call_time = time;

		//this counters are used to track when is time to make the calls
		//scince they are all multiples of each other if they are all initialized at 50
		//their calls will be in sync. Which is undesirable because sometimes all will
		//be called, and sometimes non will. This might degrade the performance.
		_0.1hr_count++;
		_1hr_count++;
		_10hr_count++;
		_50hr_count++;

		update_100hr();
		if (_50hr_count == 2) {update_50hr(); _50hr_count = 0;} // 2/100  = 1/50
		if (_10hr_count == 10) {update_10hr(); _10hr_count = 0;} // 10/100  = 1/10
		if (_1hr_count == 100) {update_1hr(); _1hr_count = 0;} // 100/100  = 1
		if (_0.1hr_count == 1000) {update_0.1hr(); _0.1hr_count = 0;} // 1000/100  = 0.1

		last_call_time = time;
	}
}

void Scheduler::update_100hr()
{

}

