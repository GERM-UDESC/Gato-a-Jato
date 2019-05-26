#ifndef ANGLE_LINE_SENSOR_H
#define ANGLE_LINE_SENSOR_H

#include "LINE_SENSOR.h"

class ANGLE_LINE_SENSOR_H : Line_Sensor
{
	private:
		float lineSensorReading{0};
		float lastLineSensorReading{0};
		float lastDistance{0};
		float angle{0};
		
	public:
		float readAngle();	
		void updateLineAngle();
}

#endif
