#ifndef __SENSOR__MPU_H
#define __SENSOR__MPU_H

#include "Scheduler.h"

#include "MPU6050_6Axis_MotionApps20.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
#include "I2Cdev.h"

class Sensor : public Process {
public:
	Sensor();

	bool init();

	void update();

	float* get_ypr();
	int* get_ypr_vel();

	// some usefull variables for debugging
	int pullMissCount;
	int pullEmptyMissCount;
	int overflowCount;
	int lastBuferReadCount;

private:
	MPU6050 mpu;

	// MPU control/status vars
	bool dmpReady;  // set true if DMP init was successful
	uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
	uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
	uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
	uint16_t fifoCount;     // count of all bytes currently in FIFO
	uint8_t fifoBuffer[64]; // FIFO storage buffer

	// orientation/motion vars
	Quaternion q;           // [w, x, y, z]         quaternion container
	VectorInt16 aa;         // [x, y, z]            accel sensor measurements
	VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
	VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
	VectorFloat gravity;    // [x, y, z]            gravity vector
	float euler[3];         // [psi, theta, phi]    Euler angle container
	float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
	int ypr_vel[3];          // [yaw, pitch, roll]   yaw/pitch/roll
};


#endif
