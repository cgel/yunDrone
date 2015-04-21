#ifndef __SENSOR_H
#define __SENSOR_H

#include "I2Cdev.h"
#include "Scheduler.h"

#include "MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050.h" // not necessary if using MotionApps include file

/*
	Serial.print("ypr\t");
	Serial.print(ypr[0] * 180/M_PI);
	Serial.print("\t");
	Serial.print(ypr[1] * 180/M_PI);
	Serial.print("\t");
*/


// Interrupt detection routine
volatile bool mpuInterrupt = false; // indicates whether MPU interrupt pin has gone high
void dmpDataReady() 
{
    mpuInterrupt = true;
}


class Sensors: public Process
{
	public:
	bool init();

	void update();

	float[] get_ypr();

	private:
	MPU6050 mpu;

	// MPU control/status vars
	bool dmpReady = false;  // set true if DMP init was successful
	uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
	uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
	uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
	uint16_t fifoCount;     // count of all bytes currently in FIFO
	uint8_t fifoBuffer[64]; // FIFO storage buffer

	// orientation/motion vars
	Quaternion q;           // [w, x, y, z]         quaternion container
	VectorFloat gravity;    // [x, y, z]            gravity vector
	float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
};


#endif
