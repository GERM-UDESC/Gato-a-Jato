#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H
#include "REFLECTANCE_SENSOR.h"

#define calib_sensores 150
#define maxTeta 0.25594 //rad
#define maxDistance 0.035

class Line_Sensor
{
private:
	float last_error;
	float erro;
	float media;
	float sensor_values[8];			//it's "int" because it might be under zero
	float soma;		

public:
//	Line_Sensor(ADC_CHANNELS ADCChannel_0, ADC_CHANNELS ADCChannel_1, ADC_CHANNELS ADCChannel_2, ADC_CHANNELS ADCChannel_3, 
//							ADC_CHANNELS ADCChannel_4, ADC_CHANNELS ADCChannel_5, ADC_CHANNELS ADCChannel_6, ADC_CHANNELS ADCChannel_7);
	Line_Sensor(Reflectance_Sensor Sensor1, Reflectance_Sensor Sensor2, Reflectance_Sensor Sensor3, Reflectance_Sensor Sensor4,
							Reflectance_Sensor Sensor5, Reflectance_Sensor Sensor6, Reflectance_Sensor Sensor7, Reflectance_Sensor Sensor8);
	Line_Sensor(Line_Sensor *lineSensor);
	Reflectance_Sensor Sensors[8];
	void calibrate(uint32_t iterations);
	float read();	

};



#endif
