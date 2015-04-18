#include <vector>

enum Frequency { 100hr, 50hr, 10hr, 1hr, .1hr };
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
}
