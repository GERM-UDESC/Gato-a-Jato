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

typedef enum{
	x,
	y,
	teta,
	Number_Of_Global_Position_Elements,
}GLOBAL_REFERENCE_POSITION;

typedef enum{
	Vx,
	Vy,
	Vteta,
	Number_Of_Global_Speed_Elements,
}GLOBAL_REFERENCE_SPEED;

typedef enum{
	V,
	w,
	Number_Of_Robot_Speed_Elements
}ROBOT_SPEED;

class Kinematic
{
	public:
		Motor motorD;
		Motor motorE;
		Line_Sensor lineSensor;
	
		float lineSensorReading{0};
		float lastLineSensorReading{0};
		float lastDistance{0};
		
		void posControl();
		float Uw[desired_size]{0};	
		float Ew[desired_size]{0};			
		
		float xPos{0};
		float yPos{0};
		float angle{0};
	
		float vMotDref;
		float vMotEref;
	
		float xRef;
		float yRef;
		float tetaRef;
	
		float VxRef;
		float VyRef;
		float VtetaRef;
	
		float vRef;
		float wRef;
		
		void handler();
		static Kinematic *ptRobot;
		
	public:
		Kinematic(Motor motorD, Motor motorE, Line_Sensor lineSensor);
	
		void reset();
		
		void setRobotSpeed(float V, float w);
		void setRobotRefereceSpeed(float Vx, float Vy, float Vteta);
		void setRobotReferecePosition(float x, float y, float teta);
		void goTo(float x, float y, float teta);
	
		float getX();
		float	getY();
		float getTeta();
		float getLineAngle();
	
		float getVx();
		float	getVy();
		float getVteta();
	
		float getV();
		float getW();
	
		void setX(float x);
		void setY(float y);
		
		void calibrateLineSensor(uint32_t iterations);
		void updateLineAngle();
	
		static void handlerByTime();


	
};

#endif
