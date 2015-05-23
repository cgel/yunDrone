#include <StandardCplusplus.h>
#include <list>
#include <set>
#include <iterator>
#include <serstream>
#include <string>
#include "Scheduler.h"
#include <Arduino.h>

using namespace std;
// aaaaaaaaaa
class Helloer: public Process {
	public:
	Helloer(): msg("") {};
	Helloer(const char * str): msg(str) {};
	~Helloer(){};

	void call() {cout << "Hello my message is:" << msg << endl;};

	private:
	string msg;
};

// <iostream> declares cout/cerr, but the application must define them
// because it's up to you what to do with them.
namespace std
{
  ohserialstream cout(Serial);
}

Scheduler sys;
Helloer* h1 = new Helloer("xx");
Helloer* h2 = new Helloer("-- xx");
Helloer h3 ("-- -- xx");

void setup(void)
{
	Serial.begin(115200);

	cout << "Starting Scheduler demo" << endl;

	sys.addProcess(*h1, _1hr);
	sys.addProcess(*h2, _10hr);
	sys.addProcess(h3, _50hr); //h3 not a pointer


	sys.loop();
}

void loop(void)
{
}

// vim:cin:ai:sts=2 sw=2 ft=cpp
