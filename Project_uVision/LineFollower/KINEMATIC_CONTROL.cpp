#include "KINEMATIC_CONTROL.h"

Kinematic *Kinematic::ptRobot;

void Kinematic::handlerByTime()
{
	Kinematic::ptRobot->handler();
}

Kinematic::Kinematic(Motor motorD, Motor motorE) : motorD(&motorD), motorE(&motorE), xPos(0), yPos(0)
{
	Kinematic::ptRobot = this;
	xPos = 0;
	yPos = 0;
}

void Kinematic::reset()
{
	motorD.reset();
	motorE.reset();
	xPos = 0;
	yPos = 0;
	lastTeta = 0;
	vRef = 0;
	wRef = 0;
	vMotDref = 0;
	vMotEref = 0;
	xRef = 0;
	yRef = 0;
	tetaRef = 0;
	VxRef = 0;
	VyRef = 0;
	VtetaRef = 0;
}

void Kinematic::setRobotSpeed(float V, float w)
{
	vRef = V;
	wRef = w;

	vMotDref = (V/r + (L*w)/r)*radsToRpm;
	vMotEref = (V/r - (L*w)/r)*radsToRpm;
	
	motorD.Set_Speed(vMotDref);
	motorE.Set_Speed(vMotEref);	
}

void Kinematic::setRobotRefereceSpeed(float Vx, float Vy, float Vteta)
{
	vMotDref = (1/r)*(Vx*cos(getTeta()) + Vy*sin(getTeta()) + L*Vteta);
	vMotEref = (1/r)*(Vx*cos(getTeta()) + Vy*sin(getTeta()) - L*Vteta);
	
	vRef = (r/(2))*(vMotDref + vMotEref);
	wRef = (r/(2*L))*(vMotDref - vMotEref);
	
	motorD.Set_Speed(vMotDref);
	motorE.Set_Speed(vMotEref);
}

void Kinematic::setRobotReferecePosition(float x, float y, float teta)
{
	xRef = x;
	yRef = y;
	tetaRef = teta;
}

void Kinematic::handler()
{
//	xPos += getV()*cos(getTeta())*integrationTime;
//	yPos += getV()*sin(getTeta())*integrationTime;
	
//	float deltaDistance, commonDistance, actualTeta;
//	actualTeta = getTeta();
//	if(motorD.getDeltaDistance() > motorE.getDeltaDistance())
//	{ 
//		commonDistance = motorE.getDeltaDistance();
//		deltaDistance = motorD.getDeltaDistance() - commonDistance;
//	}
//	else
//	{
//		commonDistance = motorD.getDeltaDistance();
//		deltaDistance = motorE.getDeltaDistance() - commonDistance;
//	}
//	xPos += commonDistance*cos(lastTeta) + deltaDistance*cos(actualTeta - lastTeta);
//	yPos += commonDistance*sin(lastTeta) + deltaDistance*sin(actualTeta - lastTeta);
//	lastTeta = actualTeta;
	float deltaDistance;
	deltaDistance = (motorD.getDeltaDistance() + motorE.getDeltaDistance())/2;
	xPos += deltaDistance*cos(getTeta());
	yPos += deltaDistance*sin(getTeta());
}

float Kinematic::getV()
{
	return (r/(2))*(motorD.getSpeedRadS() + motorE.getSpeedRadS());
}

float Kinematic::getw()
{
	return (r/(2*L))*(motorD.getSpeedRadS() - motorE.getSpeedRadS());
}

void Kinematic::setX(float x)
{
	xPos = x;
}

void Kinematic::setY(float y)
{
	yPos = y;
}

float Kinematic::getX()
{
	return xPos;		
}

float	Kinematic::getY()
{
	return yPos;		
}

float Kinematic::getTeta()
{
	return (r/(2*L))*(motorD.getTeta() - motorE.getTeta());	
}

float Kinematic::getVx()
{
	return cos(getTeta())*(r/2)*(motorD.getSpeedRadS() - motorE.getSpeedRadS());
}

float	Kinematic::getVy()
{
	return sin(getTeta())*(r/2)*(motorD.getSpeedRadS() - motorE.getSpeedRadS());
}

float Kinematic::getVteta()
{
	return (r/(2*L))*(motorD.getSpeedRadS() - motorE.getSpeedRadS());
}





