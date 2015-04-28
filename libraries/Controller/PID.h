#ifndef __PID_H
#define __PID_H

// process variable (PV) is the measured variable that we intend to control (e.g. the angle of a quadrotor)
// set point (SPT) is the "goal" for the PV
// control variable (CV) is the variable that we can manipulate to minimize abs(PV-SPT) (i.e. make the PV get to the SPT)

// this pid assumes to be called at a constant frequency. If the frequency is changed the kd must be retuned.

class PID {
public:
	//returns the CV
	int update();
	int update(int _PV, int _SPT);

//	void update();
//	void update(int _PV, int _SPT);

	void set_PV(int);
	void set_SPT(int);

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
	int SPT; // set point
	int CV; // control variable
	int err; // difference between PV and the SPT
	int err_integral;
	int err_derivative;
	int last_err;
};

#endif
