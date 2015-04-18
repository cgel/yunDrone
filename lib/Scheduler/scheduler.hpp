#include <vector>

enum Frequency { _100hr, _50hr, _10hr, _1hr, _0.1hr };
typedef std::vector<Process *>::Iterator pid_t;

// pid here means process identifier

// derive from this class to create a usable process
class Process {
	public:
	Process()
	virtual ~Process()

	virtual void update(); //The main function that must be defined when deriving this class.

	pid_t getPid() const {return pid;};
	
	void setPid(pid_t p) {pid = p;}; // ony to be used by class Scheduler

	private:
	pid_t pid = -1; // default pid not valid
	const Frequency freq;
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
	std::vector<Process *> Processes;
	short int _0.1hr_count;
	short int _1hr_count;
	short int _10hr_count;
	short int _50hr_count;
	unsigned long time;
	unsigned long last_call_time;
}
