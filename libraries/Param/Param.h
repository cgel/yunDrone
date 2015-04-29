#ifndef __PARAM_H_ 
#define __PARAM_H_
#include <EEPROM.h>

class Param {
public:
	float* get_r_kpid();
	void set_r_kpid(float*);

	float* get_p_kpid();
	void set_p_kpid(float*);

	float* get_y_kpid();
	void set_y_kpid(float*);


	float* get_r_vel_kpid();
	void set_r_vel_kpid(float*);

	float* get_p_vel_kpid();
	void set_p_vel_kpid(float*);

	float* get_y_vel_kpid();
	void set_y_vel_kpid(float*);


	float* get_gyro_offsets();
	void get_gyro_offsets(float*);

private:
	template <class T> int EEPROM_write(int ee, const T& value)
	{
	   const byte* p = (const byte*)(const void*)&value;
	   int i;
	   for (i = 0; i < sizeof(value); i++)
		   EEPROM.write(ee++, *p++);
	   return i;
	}

	template <class T> int EEPROM_read(int ee, T& value)
	{
	   byte* p = (byte*)(void*)&value;
	   int i;
	   for (i = 0; i < sizeof(value); i++)
		   *p++ = EEPROM.read(ee++);
	   return i;
	}
}

#endif
