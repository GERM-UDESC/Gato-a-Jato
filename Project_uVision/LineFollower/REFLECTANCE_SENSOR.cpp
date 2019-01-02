#include "REFLECTANCE_SENSOR.h"
Reflectance_Sensor::Reflectance_Sensor()
{
	calib_max = 2000;		//initialize the variable
	calib_min = 2000;		//initialize the variable	
}

Reflectance_Sensor::Reflectance_Sensor(ADC_CHANNELS ADCChannel) : ADC(ADCChannel)
{
	calib_max = 2000;		//initialize the variable
	calib_min = 2000;		//initialize the variable
}

void Reflectance_Sensor::Calib_Reflectance_Sensor()
{
	uint16_t sensor_value = analogRead();
	if (sensor_value < calib_min)
	{
		calib_min = sensor_value;
	}
  if (sensor_value > calib_max)
	{
		calib_max = sensor_value;
	}
	range = calib_max - calib_min;
}

uint16_t Reflectance_Sensor::Reflectance_Read()
{
	uint16_t Converted_read = analogRead();
	Converted_read = 1000 * (calib_max - Converted_read) / range;

	return Converted_read;
}
