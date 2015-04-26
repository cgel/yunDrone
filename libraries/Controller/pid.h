#ifndef __PID_H
#define __PID_H

// process variable (PV) is the measured variable that we intend to control (e.g. the angle of a quadrotor)
// set point (SP) is the "goal" for the PV
// control variable (CV) is the variable that we can manipulate to minimize abs(PV-SP) (i.e. make the PV get to the SP)

class PID {
public:
	//returns the CV
	int update();
	int update(int _PV, int _SP);
	
	void update();
	void update(int _PV, int _SP);

	void set_PV(int);
	void set_SP(int);

	int get_CV();

	void set_kp(int k);
	void set_ki(int k);
	void set_kd(int k);
	void set_kpid(int p, int i, int d);

	void reset_state();

private:
	// Parameters
	int kp;
	int ki;
	int kd;

	// Values of state
	int PV; // process variable
	int PV_derivative;
	int PV_integral;
	int SP; // set point
	int CV; // control variable
}

#endif
