void PID::update() {
	// MAYBE TO DO: remove high frequency noise form the error, or the error derivative.
	err = abs(PV - SP);

	// update the integral
	err_integral += err;	

	// update the derivative 
	err_derivative = err - last_err;

	CV = kp*err + ki*err_integral + kd*err_derivative;
}

void PID::update(int _PV, int _SP) {
	set_PV(_PV);
	set_SP(_SP);
	update();
}

int PID::update() {
	update();
	return CV;
}

int PID::update(int _PV, int _SP) {
	set_PV(_PV);
	set_SP(_SP);
	update();
	return CV;
}

void PID::set_PV(int _PV) {
	PV = _PV;
}

void PID::set_SP(int _SP) {
	SP = _SP;
}

int PID::get_CV() {
	return CV;
}

void PID::set_kp(int k) {
	kp =k;
}

void PID::set_ki(int k) {
	ki = i;
}

void PID::set_kd(int k) {
	kd = d;
}

void PID::set_kpid(int p, int i, int d) {
	set_kd(k);
	set_kp(p);
	set_kd(d);
}

void PID::reset_state() {
	err_derivative = 0;
	err_integral = 0;
}
