#ifndef KINEMATIC_CONTROL_H
#define KINEMATIC_CONTROL_H

#include "MOTOR.h"
#include "math.h"

#define L 0.079

#define integrationTime Time_between_int/1000000

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
		float xPos{0};
		float yPos{0};
		float lastTeta{0};
	
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
		static Kinematic *ptRobot;
		
		void handler();
		
	public:
		Kinematic(Motor motorD, Motor motorE);
	
		void reset();
		
		void setRobotSpeed(float V, float w);
		void setRobotRefereceSpeed(float Vx, float Vy, float Vteta);
		void setRobotReferecePosition(float x, float y, float teta);
		void goTo(float x, float y, float teta);
	
		float getX();
		float	getY();
		float getTeta();
	
		float getVx();
		float	getVy();
		float getVteta();
	
		float getV();
		float getw();
	
		void setX(float x);
		void setY(float y);
	
		static void handlerByTime();


	
};

#endif
