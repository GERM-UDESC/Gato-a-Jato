#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H
#include "REFLECTANCE_SENSOR.h"

class Line_Sensor
{
private:
	Reflectance_Sensor Sensors[8];
	static const uint16_t calib_sensores = 150;

public:
	Line_Sensor(ADC_CHANNELS ADCChannel_0, ADC_CHANNELS ADCChannel_1, ADC_CHANNELS ADCChannel_2, ADC_CHANNELS ADCChannel_3, 
							ADC_CHANNELS ADCChannel_4, ADC_CHANNELS ADCChannel_5, ADC_CHANNELS ADCChannel_6, ADC_CHANNELS ADCChannel_7);

	void Calibrate_Sensor();
	uint16_t Read_Sensor();	

};



#endif
