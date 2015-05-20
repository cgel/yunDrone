#include <StandardCplusplus.h>
#include <serstream>

#include "MPU6050_6Axis_MotionApps20.h"

#include "Scheduler.h"
#include "Sensor.h"
#include "Controller.h"
#include "PID.h"


#include <Wire.h>
#include <I2Cdev.h>

#include <Arduino.h>

using namespace std;


// <iostream> declares cout/cerr, but the application must define them
// because it's up to you what to do with them.
namespace std
{
  ohserialstream cout(Serial);
}


Scheduler sys;
Controller* ctrl = new Controller();

class Writer: public Process {
	public:
	Writer() {}
	~Writer(){}

	void update() 
	{
		//float* ypr = sens->get_ypr();
		// int* ypr_vel = sens->get_ypr_vel();
		// cout <<"- "<<ypr[0]<<" - "<<ypr[1]<<" - "<<ypr[2]<<"- "<<ypr_vel[0]<<" - "<<ypr_vel[1]<<" - "<<ypr_vel[2]<< endl;
	};
};

Writer* w = new Writer();

void setup(void)
{
	Serial.begin(38400);
	cout << "Starting controller demo" << endl;
	//sensor return 0 if everything is ok
	if(ctrl->all_good())
	{
		//cout << "Sensor initialized" << endl;
		sys.addProcess(ctrl, _100hr);
		sys.addProcess(w, _10hr);
	}
	else cout << "Controller is not okay" << endl;
}

void loop(void)
{
	sys.update();
}
