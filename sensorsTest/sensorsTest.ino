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
/*
namespace std
{
  ohserialstream cout(Serial);
}
*/

Scheduler sys;
Sensor* sens = new Sensor();

/*
class Writer: public Process {
	public:
	Writer() {};
	~Writer(){};

	void update() 
	{
		float* ypr = sens->get_ypr();
		int ofc = sens->overflowCount;
		int pm = sens->pullMissCount;
		int pem = sens->pullEmptyMissCount;
		int rc = sens->lastBuferReadCount;
		cout <<"- "<<ypr[0]<<" - "<<ypr[1]<<" - "<<ypr[2]<<" - "<<" - overflow: "<<ofc<<" - empty miss: "<<pem<<" - miss: "<<pm<<" - readCount: "<<rc<< endl;
	};
};

Writer* w = new Writer();
*/

void setup(void)
{
	Serial.begin(38400);
	//cout << "Starting sensors demo" << endl;
	Serial.println(F("Starting sensors demo\n"));
	//sensor return 0 if everything is ok
	if(!sens->init())
	{
		// cout << "Sensor initialized" << endl;
		sys.addProcess(sens, _100hr);
		//sys.addProcess(w, _10hr);
	}
	//else cout << "Sensor could not be initialized" << endl;
}

void loop(void)
{
	sys.update();
}
