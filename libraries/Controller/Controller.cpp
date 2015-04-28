#include "Controller.h"

Controller::Controller(): sensor() {}

void Controller::init() {
/*
	roll_pid;	
	pitch_pid;	
	yaw_pid;	

	roll_vel_pid;	
	pitch_vel_pid;	
	yaw_vel_pid;	
*/
}

void Controller::update_motors() {
	roll_vel_pid.get_CV();	
	pitch_vel_pid.get_CV();	
	yaw_vel_pid.get_CV();	
}

void Controller::update() {
	float* ypr = sensor.get_ypr();
	float yaw = ypr[0];	
	float pitch = ypr[1];	
	float roll = ypr[2];	
	int r_contr = roll_pid.update(roll, roll_goal);	
	int p_contr = pitch_pid.update(pitch, pitch_goal);	
	int y_contr = yaw_pid.update(yaw, yaw_goal);	

	int* ypr_vel = sensor.get_ypr_vel();
	int yaw_vel = ypr_vel[0];	
	int pitch_vel = ypr_vel[1];
	int roll_vel = ypr_vel[2];	
	roll_vel_pid.update(roll_vel , r_contr);	
	pitch_vel_pid.update(pitch_vel ,p_contr);	
	yaw_vel_pid.update(yaw_vel , y_contr);	

	update_motors();
}

void Controller::set_rpy_goal(int r, int p, int y) {
	roll_goal = r;
	pitch_goal = p;
	yaw_goal = y;
}

void Controller::set_rpy_goal(int* rpy) {
	roll_goal = rpy[0];
	pitch_goal = rpy[1];
	yaw_goal = rpy[2];
}

bool Controller::all_good() {
	return true;
}
