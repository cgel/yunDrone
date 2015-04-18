#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <Scheduler.h>
#include <Arduino.h>

using namespace std;

class Helloer: public Process {
	public:
	Helloer(): msg("") {};
	Helloer(const char * str): msg(str) {};
	~Helloer(){};

	void update() {cout << "Hello my message is:" << msg << endl;};

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
Helloer* h3 = new Helloer("-- -- xx");

void setup(void)
{
	Serial.begin(57600);

	cout << "Starting Scheduler demo" << endl;

	sys.addProcess(h1, _1hr);
	sys.addProcess(h2, _10hr);
	sys.addProcess(h3, _50hr);
}

void loop(void)
{
	sys.update();
}

// vim:cin:ai:sts=2 sw=2 ft=cpp
