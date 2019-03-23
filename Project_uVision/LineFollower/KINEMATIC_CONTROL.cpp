#include "KINEMATIC_CONTROL.h"

Kinematic::Kinematic(Motor motorD, Motor motorE) : motorD(&motorD), motorE(&motorE)
{
	
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
	
	vRef = (1/(2*r))*(vMotDref + vMotEref);
	wRef = (1/(2*r))*(vMotDref - vMotEref);
	
	motorD.Set_Speed(vMotDref);
	motorE.Set_Speed(vMotEref);
}

float Kinematic::getX()
{
	return 0;		
}

float	Kinematic::getY()
{
	return 0;		
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





