#ifndef KINEMATIC_CONTROL_H
#define KINEMATIC_CONTROL_H

#include "MOTOR.h"
#include "math.h"

#define L 0.1
#define r 0.016

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
	
		float vMotDref;
		float vMotEref;
		float Vteta;
	
		float vRef;
		float wRef;
	
		float getX();
		float	getY();
		float getTeta();
	
		float getVx();
		float	getVy();
		float getVteta();
	
		
	public:
		Kinematic(Motor motorD, Motor motorE);
		void setRobotSpeed(float V, float w);
		void setRobotRefereceSpeed(float Vx, float Vy, float Vteta);


	
	
	
	
	
	
};

#endif
