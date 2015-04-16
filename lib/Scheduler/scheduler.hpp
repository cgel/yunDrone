
enum Frequency { 100hr, 50hr, 10hr, 1hr, .1hr };

class Process {
	public:
	Process(int pid)
	virtual void operator()(); //The main function that must be defined when deriving this class.
	int getPid() const {return pid;};

	private:
	const short int pid;
	Frequency freq;
};

class Scheduler {
	public:
	Scheduler(): nextPid(0);	

	private:
	vector<Process> Processes;
	short int nextPid;
}
