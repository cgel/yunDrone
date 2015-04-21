#include <StandardCplusplus.h>
#include <serstream>
#include <Wire.h>
#include <I2Cdev.h>
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

Sensor sens;

void setup(void)
{
	Serial.begin(57600);
	cout << "Starting sensors demo" << endl;

	bool sensorState = sens.sensorInit();	
	//sensor return 0 if everything is ok
	if(!sensorState)
	{
		cout << "Sensors have been initialized" << endl;
	}
	else cout << "Sensors could not be initialized" << endl;
}

void loop(void)
{
	sens.sensorUpdate();
}
