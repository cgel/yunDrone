#include <vector>

enum Frequency { _100hr = 0, _50hr = 1, _10hr = 2, _1hr = 3, _0.1hr = 4 };

// A list is used because the iterators are never invalidated
typedef std::list<Process *>::Iterator pid_t;

// pid here means process identifier
class pid_t {
	const Frequency first;
	const short int second;
}

// derive from this class to create a usable process
class Process {
	public:
	Process()
	virtual ~Process()

	virtual void update(); //The main function that must be defined when deriving this class.

	private:
};


class Scheduler {
	// pid here means process identifier
	public:
	Scheduler();	
	~Scheduler();

	pid_t addProcess(Process * pr, Frequency freq);
	void killProcess(pid_t pid);

	void update();

	private:

	// processes is a vector of iterators
	std::array<std::list<Process *>, 5> processes;

	short int _0.1hr_count;
	short int _1hr_count;
	short int _10hr_count;
	short int _50hr_count;
	unsigned long time;
	unsigned long last_call_time;
}
