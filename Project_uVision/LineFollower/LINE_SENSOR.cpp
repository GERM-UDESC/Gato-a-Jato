#include "LINE_SENSOR.h"

Line_Sensor::Line_Sensor(Reflectance_Sensor Sensor1, Reflectance_Sensor Sensor2, 
												 Reflectance_Sensor Sensor3, Reflectance_Sensor Sensor4,
												 Reflectance_Sensor Sensor5, Reflectance_Sensor Sensor6, 
												 Reflectance_Sensor Sensor7, Reflectance_Sensor Sensor8)
: Sensors{&Sensor1, &Sensor2, &Sensor3, &Sensor4, &Sensor5, &Sensor6, &Sensor7, &Sensor8}
{
	for (int i = 0; i < (sensorFilterOrder); i++)
	{
		erro[i] = 0;
	};
}

Line_Sensor::Line_Sensor(Line_Sensor *lineSensor)
: Sensors{&lineSensor->Sensors[0], &lineSensor->Sensors[1], &lineSensor->Sensors[2], &lineSensor->Sensors[3],
					&lineSensor->Sensors[4], &lineSensor->Sensors[5], &lineSensor->Sensors[6], &lineSensor->Sensors[7]}
{
	for (int i = 0; i < (sensorFilterOrder); i++)
	{
		erro[i] = 0;
	};
}


void Line_Sensor::calibrate(uint32_t iterations)
{
	for(int j = 0; j < iterations; j++)
	{
		for(int i = 0; i < 8; i++)
		{
			Sensors[i].Calib_Reflectance_Sensor();
		}
	}
}

float Line_Sensor::read()
{
	media = 0;
	soma = 0;
	for (int i = 0; i < (sensorFilterOrder-1); i++)
	{
		erro[i] = erro[i+1];
	};	
	
	for (int i = 0; i < 8; i++)
  {
		sensor_values[i] = Sensors[i].Reflectance_Read();	//Read the sensor
		if (sensor_values[i] > calib_sensores)						//verify if it's not just some ruid
    {
      media += i * (sensor_values[i]);
      soma += sensor_values[i];
    }
  }

	if (soma != 0)		//only calculate the error if the sum is diferent of 0
	{

		erro[sensorFilterOrder-1] = (media/soma) - 3.5;
		erro[sensorFilterOrder-1] = maxDistance*erro[sensorFilterOrder-1];
		erro[sensorFilterOrder-1] = erro[sensorFilterOrder-1]/3.5;
		if (erro[sensorFilterOrder-1] > maxDistance)
			erro[sensorFilterOrder-1] = maxDistance;
		else if (erro[sensorFilterOrder-1] < -maxDistance)
			erro[sensorFilterOrder-1] = -maxDistance;
	}

	filteredError = 0;
	for (int i = 0; i < (sensorFilterOrder); i++)
	{
		filteredError += erro[i];
	};
	filteredError = filteredError/sensorFilterOrder;

	return filteredError; 
}

float Line_Sensor::readNotFiltered()
{
	return erro[sensorFilterOrder-1];
}

