#ifndef __CONTROLLER_H
#include "Scheduler.h"
#include "Sensor.h"
#include "PID.h"

class Controller: public Process {
public:
	Controller();

	void init();

	void update();

	void set_y_goal(float y);
	void set_p_goal(float p);
	void set_r_goal(float r);
	void set_rpy_goal(float r, float p, float y);
	void set_rpy_goal(float* rpy); //pass an array

	bool all_good();

	PID<float> roll_pid;	
	PID<float> pitch_pid;	
	PID<float> yaw_pid;	

	PID<float> roll_vel_pid;	
	PID<float> pitch_vel_pid;	
	PID<float> yaw_vel_pid;	


private:
	Sensor sensor;

	float roll_goal;
	float pitch_goal;
	float yaw_goal;


	void update_motors();
};

#endif
