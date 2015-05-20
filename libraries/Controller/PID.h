#ifndef __PID_H
#define __PID_H

// process variable (PV) is the measured variable that we intend to control (e.g. the angle of a quadrotor)
// set point (SPT) is the "goal" for the PV
// control variable (CV) is the variable that we can manipulate to minimize abs(PV-SPT) (i.e. make the PV get to the SPT)

// this pid assumes to be called at a constant frequency. If the frequency is changed the kd must be retuned.

// normally int or float
template<class T>
class PID {
public:
	//returns the CV
	T update();
	T update(T _PV, T _SPT);

//	void update();
//	void update(T _PV, T _SPT);

	void set_PV(T);
	void set_SPT(T);

	T get_CV();

	void set_kp(T k);
	void set_ki(T k);
	void set_kd(T k);
	void set_kpid(T p, T i, T d);

	void reset_state();


private:
	// Parameters
	T kp;
	T ki;
	T kd;

	// Values of state
	T PV; // process variable
	T SPT; // set point
	T CV; // control variable
	T err; // difference between PV and the SPT
	T err_integral;
	T err_derivative;
	T last_err;
};



template<class T>
T PID<T>::update() {
	// MAYBE TO DO: remove high frequency noise form the error, or the error derivative.
	err = abs(PV - SPT);

	// update the integral
	err_integral += err;	

	// update the derivative 
	err_derivative = err - last_err;

	CV = kp*err + ki*err_integral + kd*err_derivative;
	return CV;
}

template<class T>
T PID<T>::update(T _PV, T _SPT) {
	set_PV(_PV);
	set_SPT(_SPT);
	update();
	return CV;
}

template<class T>
void PID<T>::set_PV(T _PV) {
	PV = _PV;
}

template<class T>
void PID<T>::set_SPT(T _SPT) {
	SPT = _SPT;
}

template<class T>
T PID<T>::get_CV() {
	return CV;
}

template<class T>
void PID<T>::set_kp(T k) {
	kp =k;
}

template<class T>
void PID<T>::set_ki(T k) {
	ki = k;
}

template<class T>
void PID<T>::set_kd(T k) {
	kd = k;
}

template<class T>
void PID<T>::set_kpid(T p, T i, T d) {
	set_kd(p);
	set_kp(i);
	set_kd(d);
}

template<class T>
void PID<T>::reset_state() {
	err_derivative = 0;
	err_integral = 0;
}

#endif
