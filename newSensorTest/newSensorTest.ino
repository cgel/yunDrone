#include <StandardCplusplus.h>
#include <serstream>
#include <Wire.h>
#include <I2Cdev.h>
#include "Scheduler.h"
#include <Arduino.h>
#include "Sensor.h"
#include "MPU6050.h"

using namespace std;


// <iostream> declares cout/cerr, but the application must define them
// because it's up to you what to do with them.
namespace std
{
  ohserialstream cout(Serial);
}

Scheduler sys;
Sensor* sens;

void setup(void)
{
	Serial.begin(57600);
	cout << "Starting sensors demo" << endl;
	//sensor return 0 if everything is ok
	if(!sens->init())
	{
		cout << "Sensors have been initialized" << endl;
		sys.addProcess(sens, _100hr);
	}
	else cout << "Sensors could not be initialized" << endl;
}

void loop(void)
{
	sys.update();
}

// vim:cin:ai:sts=2 sw=2 ft=cpp
