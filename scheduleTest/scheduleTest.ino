#include "Scheduler.h"
#include "Heap.h"
#include <Arduino.h>

using namespace std;
// aaaaaaaaaa
class Helloer: public Process {
	public:
	Helloer(): msg("") {};
	Helloer(const char * str): msg(str) {};
	~Helloer(){};

	//void call() {cout << "Hello my message is:" << msg << endl;};
	void call() {Serial.print(msg);};

	private:
	const char *msg;
};

Scheduler sys;
Helloer* h1 = new Helloer("a\n");
Helloer* h2 = new Helloer("-- xx");
Helloer h3 ("-- -- xx");

void setup(void)
{
	Serial.begin(115200);

	//cout << "Starting Scheduler demo" << endl;

	sys.addProcess(*h1, 5000);
	//sys.addProcess(*h2, 3000);
	//sys.addProcess(h3,  20); //h3 not a pointer

	Serial.begin(115200);

	sys.loop();
}

void loop(void)
{
}

// vim:cin:ai:sts=2 sw=2 ft=cpp
