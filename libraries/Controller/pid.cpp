#include "Controller.h"

Controller::init() {
/*
	roll_pid;	
	pitch_pid;	
	yaw_pid;	

	roll_vel_pid;	
	pitch_vel_pid;	
	yaw_vel_pid;	
*/
}

Controller::update() {
	int* rpy = sensor.get_rpy();
	int roll = rpy[0];	
	int pitch = rpy[1];	
	int yaw = rpy[2];	
	int r_contr = roll_pid.update(roll, roll_goal);	
	int p_contr = pitch_pid.update(pitch, pitch_goal);	
	int y_contr = yaw_pid.update(yaw, yaw_goal);	

	int* rpy_vel = sensor.get_rpy_vel();
	int roll_vel = rpy_vel[0];	
	int pitch_vel = rpy_vel[1];
	int yaw_vel = rpy_vel[2];	
	int roll_force = roll_vel_pid.update(roll_vel , r_contr);	
	int pitch_force = pitch_vel_pid.update(pitch_vel ,p_contr);	
	int yaw_force = yaw_vel_pid.update(yaw_vel , y_contr;	

	// update the motors inputs
}

Controller::set_rpy_goal(int r, int p, int y) {
	roll_goal = r;
	pitch_goal = p;
	yaw_goal = y;
}

Controller::set_rpy_goal(int* rpy) {
	roll_goal = rpy[0];
	pitch_goal = rpy[1];
	yaw_goal = rpy[2];
}
