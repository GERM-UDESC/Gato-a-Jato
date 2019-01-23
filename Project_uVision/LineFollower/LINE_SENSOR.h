#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H
#include "REFLECTANCE_SENSOR.h"

#define calib_sensores 100

class Line_Sensor
{
private:
	Reflectance_Sensor Sensors[8];

public:
	Line_Sensor(ADC_CHANNELS ADCChannel_0, ADC_CHANNELS ADCChannel_1, ADC_CHANNELS ADCChannel_2, ADC_CHANNELS ADCChannel_3, 
							ADC_CHANNELS ADCChannel_4, ADC_CHANNELS ADCChannel_5, ADC_CHANNELS ADCChannel_6, ADC_CHANNELS ADCChannel_7);

	void Calibrate_Sensor();
	float Read_Sensor();	

};



#endif
