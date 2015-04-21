#include <Scheduler.h>

// CLASS SCHEDULER
Scheduler::Scheduler()	
{	
	_50hr_count = 1;
	_10hr_count = 2;
	_1hr_count = 3; 
	_0p1hr_count = 4;
}

Scheduler::~Scheduler()
{
	// this class manages mem in the free store but no need to bother deleting it since this class will never be destroied
}

pid_t Scheduler::addProcess(Process * pr, const Frequency freq)
{
	processes[freq].push_back(pr);
	pid_t pid(freq, processes[freq].end() );
	return pid;
}

void Scheduler::killProcess(const pid_t& pid)
{
	processes[pid.first].erase(pid.second);
}

void Scheduler::update()
{
	// keep a base "call clock" of a 100hr
	// Lower frequency calls +++ count of a base 
	time = millis();	
	if (time - last_call_time > 10) // 10 milliseconds 
	{
		last_call_time = time;

		//this counters are used to track when is time to make the calls
		//scince they are all multiples of each other if they are all initialized at 50
		//their calls will be in sync. Which is undesirable because sometimes all will
		//be called, and sometimes non will. This might degrade the performance.
		_0p1hr_count++;
		_1hr_count++;
		_10hr_count++;
		_50hr_count++;

		for (auto i : processes[_100hr])
		{
			i->update();	
		}

		if (_50hr_count == 2)  // 2/100  = 1/50
		{
			for (auto i : processes[_50hr])
			{
				i->update();	
			}
			_50hr_count = 0;
		}

		if (_10hr_count == 10) // 10/100  = 1/10
		{
			for (auto i : processes[_10hr])
			{
				i->update();	
			}
			_10hr_count = 0;
		} 

		if (_1hr_count == 100) // 100/100  = 1
		{
			for (auto i : processes[_1hr])
			{
				i->update();	
			}
			_1hr_count = 0;
		} 

		if (_0p1hr_count == 1000) // 1000/100  = 0.1
		{
			for (auto i : processes[_0p1hr])
			{
				i->update();	
			}
			_0p1hr_count = 0;
		}

		last_call_time = time;
	}
}
