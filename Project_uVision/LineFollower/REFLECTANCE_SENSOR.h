#ifndef REFLECTANCE_SENSOR_H
#define REFLECTANCE_SENSOR_H
#include "ADC.h"

class Reflectance_Sensor : protected ADC
{
	friend class Line_Sensor;
private:
	uint16_t calib_max;
	uint16_t calib_min;
	uint16_t range;

protected:
	Reflectance_Sensor();
	
public:
	Reflectance_Sensor(Reflectance_Sensor *Sensor);
	Reflectance_Sensor(ADC_CHANNELS ADCChannel);

	void Calib_Reflectance_Sensor(); 	//Calibrate the sensor - This function should be called a lot at the beggining
	float Reflectance_Read();			//Should Return a value from 0 to 1000 if its very well calibrated

};

#endif
