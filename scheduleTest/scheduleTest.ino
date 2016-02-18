#include "Scheduler.h"
#include "Heap.h"
#include <Arduino.h>

using namespace std;
class Talker: public Process {
	public:

	void call() {
    Serial.print(msg);
  };

  void set_msg(const char* str)
  {
    msg = str;
  }

	private:
	  const char *msg;
};

Scheduler sys;

Talker procs[2];

void setup(void)
{
	Serial.begin(1200);

	Serial.print("Starting Scheduler demo\n");
  delay(500);
  procs[0].set_msg("my rate is 1000");
  sys.addProcess(procs[0], 1000);

  procs[1].set_msg("my rate is 2000");
  sys.addProcess(procs[1], 2000);
}

void loop(void)
{
	sys.loop();
}
