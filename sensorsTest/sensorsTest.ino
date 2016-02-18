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

class Talker: public Process {
	public:
	void call() {
    if(!sens.ready()){
      Serial.println("sensor not ready");
      return;
    } else {
      sens.print();
    }
  };
};

Scheduler sys;
Sensor sens;
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
