#ifndef __SENSOR__MPU_H
#define __SENSOR__MPU_H

#include "Scheduler.h"
#include <Wire.h>
#include "I2Cdev.h"
#include "RTIMUSettings.h"
#include "RTIMU.h"
#include "RTFusionRTQF.h" 
#include "CalLib.h"
#include <EEPROM.h>


class Sensor: public Process{
public:
	bool init();
	void call();
  bool ready(); // the imu might not be ready for a few seconds after init
	float* get_ypr();
	int* get_ypr_vel();

  bool biasValidChanged;
  void print();
private:
  RTIMU *imu;                                           // the IMU object
  RTFusionRTQF fusion;                                  // the fusion object
  RTIMUSettings settings;                               // the settings object

  //
  bool biasValid;
  bool prevBiasValid;

	//float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
	float rpy[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
	//int ypr_vel[3];          // [yaw, pitch, roll]   yaw/pitch/roll
};

#endif
