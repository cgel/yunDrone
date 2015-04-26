#ifndef __CONTROLLER_H
#define __CONTROLLER_H
#include "Scheduler.h"
#include "PID.h"

class Controller: public Process {
public:
	void init();

	void update();

	void set_rpy_goal(int r, int p, int y);
	void set_rpy_goal(int* rpy); //pass an array

private:
	Sensor sensor;

	int roll_goal;
	int pitch_goal;
	int yaw_goal;

	PID roll_pid;	
	PID pitch_pid;	
	PID yaw_pid;	

	PID roll_vel_pid;	
	PID pitch_vel_pid;	
	PID yaw_vel_pid;	
}

#endif
