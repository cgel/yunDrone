#include "Scheduler.h"
#include "Heap.h"
#include "Sensor.h"

#include <Wire.h>
#include <I2Cdev.h>

#include <Arduino.h>

#include "RTIMUSettings.h"
#include "RTIMU.h"
#include "RTFusionRTQF.h" 
#include "CalLib.h"
#include <EEPROM.h>

Scheduler sys;

Sensor sens;

class Talker: public Process {
	public:
	//void call() {cout << "Hello my message is:" << msg << endl;};
	void call() {
  if(!sens.ready()){
    Serial.println("sensor not ready");
    return;
  }
  sens.print();
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
Talker tlkr;
void setup()
{
	Serial.begin(38400);
  sys.addProcess(sens, 20);
  sys.addProcess(tlkr, 200);
  sens.init();
}

void loop(void)
{
  sys.loop();
}
