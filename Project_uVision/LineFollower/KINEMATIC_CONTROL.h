#ifndef KINEMATIC_CONTROL_H
#define KINEMATIC_CONTROL_H

#include "MOTOR.h"
#include "LINE_SENSOR.h"
#include "math.h"

#define L 0.069

#define integrationTime Time_between_int/1000000

#define Kw 455.5
#define Pw 12.97

#define ts_w 0.05 							//tempo de assentamento
#define KDw 4/(Kw*ts_w)
#define KPw Pw*KDw

class Kinematic
{
	public:
		Motor motorD;
		Motor motorE;
		Line_Sensor lineSensor;
	
		bool calibrationFinished{0};
		
		float lineSensorReading{0};
		float lastLineSensorReading{0};
		float lastDistance{0};	
		
		float xPos{0};
		float yPos{0};
		float angle{0};
		
		void handler();
		static Kinematic *ptRobot;
		
	public:
		Kinematic(Motor motorD, Motor motorE, Line_Sensor lineSensor);
		Kinematic(Kinematic *kinematic);
	
		void reset();
		
		void setSpeed(float V, float w);
	
		float getX();
		float	getY();
		float getTeta();
	
		float getLineAngle();
		float getLinePosition();
	
		float getV();
		float getW();
		
		void calibrateLineSensor(uint32_t iterations);
		void updateLineAngle();
	
		static void handlerByTime();

};

#endif
