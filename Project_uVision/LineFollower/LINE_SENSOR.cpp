#include "LINE_SENSOR.h"

Line_Sensor::Line_Sensor(ADC_CHANNELS ADCChannel_0, ADC_CHANNELS ADCChannel_1, ADC_CHANNELS ADCChannel_2, ADC_CHANNELS ADCChannel_3, 
												 ADC_CHANNELS ADCChannel_4, ADC_CHANNELS ADCChannel_5, ADC_CHANNELS ADCChannel_6, ADC_CHANNELS ADCChannel_7)
{
	Sensors[0].SetADCChannel(ADCChannel_0);
	Sensors[1].SetADCChannel(ADCChannel_1);
	Sensors[2].SetADCChannel(ADCChannel_2);
	Sensors[3].SetADCChannel(ADCChannel_3);
	Sensors[4].SetADCChannel(ADCChannel_4);
	Sensors[5].SetADCChannel(ADCChannel_5);
	Sensors[6].SetADCChannel(ADCChannel_6);
	Sensors[7].SetADCChannel(ADCChannel_7);
	
	int i = 0;
	for(i = 0; i < 8; i++)
	{
		Sensors[i].ConfigADCPin();
	}

};

void Line_Sensor::Calibrate_Sensor()
{
	int i = 0;
	for(i = 0; i < 8; i++)
	{
		Sensors[i].Calib_Reflectance_Sensor();
	}
}

float Line_Sensor::Read_Sensor()
{
	int sensor_values[8];			//it's "int" because it might be under zero
	uint32_t media;						
	uint32_t soma;
	float erro;
	
	for (int i = 0; i < 8; i++)
  {
		sensor_values[i] = Sensors[i].Reflectance_Read();	//Read the sensor
    if (sensor_values[i] > calib_sensores)						//verify if it's not just some ruid
    {
      media += i * (sensor_values[i]);
      soma += sensor_values[i];
    }
  }
	//I'll make the count by steps to asure that i'm not lossing data
	erro = 1000*media;  		//This step is why erro is 32 bits
	erro = (float)erro/soma;
	erro = erro - 3500;
 
	
	return erro; 
}

