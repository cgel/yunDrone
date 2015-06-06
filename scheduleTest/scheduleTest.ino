#include "Scheduler.h"
#include "Heap.h"
#include <Arduino.h>

using namespace std;
class Talker: public Process {
	public:
	//void call() {cout << "Hello my message is:" << msg << endl;};
	void call() {
  Serial.print(msg);
    Serial.print(m);
  };

  void set_msg(const char* str, int _m)
  {
    msg = str;
    m = _m;
  }

	private:
        int m;
	const char *msg;
};

Scheduler sys;

Talker procs[2];

void setup(void)
{
	Serial.begin(1200);

	Serial.print("Starting Scheduler demo\n");
delay(500);
        const char * str = "This is my rate";
        Serial.print(*str);
        delay(500);
  procs[0].set_msg(str, 1000);
  sys.addProcess(procs[0], 1000);

  procs[1].set_msg(str, 2000);
  sys.addProcess(procs[1], 2000);
}

void loop(void)
{
	sys.loop();
}
