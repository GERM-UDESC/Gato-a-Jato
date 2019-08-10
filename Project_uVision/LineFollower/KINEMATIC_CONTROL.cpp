#include "KINEMATIC_CONTROL.h"

Kinematic *Kinematic::ptRobot;

void Kinematic::handlerByTime()
{
	Kinematic::ptRobot->handler();
}

Kinematic::Kinematic(Motor motorD, Motor motorE, Line_Sensor lineSensor) 
: motorD(&motorD), motorE(&motorE), lineSensor(&lineSensor), xPos(0), yPos(0)
{
	Kinematic::ptRobot = this;
	calibrationFinished = 0;
	reset();
}

Kinematic::Kinematic(Kinematic *kinematic):motorD(&kinematic->motorD), motorE(&kinematic->motorE), 
lineSensor(&kinematic->lineSensor), xPos(0), yPos(0)
{
	Kinematic::ptRobot = this;
	reset();
}

void Kinematic::reset()
{
	motorD.reset();
	motorE.reset();
	xPos = 0;
	yPos = 0;
	angle = 0;
	lineSensorReading = 0;
	lastLineSensorReading = 0;
	distance = 0;
	lastDistance = 0;
}

void Kinematic::setSpeed(float V, float w)
{
	motorD.Set_Speed((V/r + (L*w)/r)*radsToRpm);
	motorE.Set_Speed((V/r - (L*w)/r)*radsToRpm);	
}

void Kinematic::handler()
{
//	xPos += getV()*cos(getTeta())*integrationTime;
//	yPos += getV()*sin(getTeta())*integrationTime;
	
	float deltaDistance;
	deltaDistance = (motorD.getDeltaDistance() + motorE.getDeltaDistance())/2;
	xPos += deltaDistance*cos(getTeta());
	yPos += deltaDistance*sin(getTeta());
	
}

float Kinematic::getV()
{
	return (r/(2))*(motorD.getSpeedRadS() + motorE.getSpeedRadS());
}

float Kinematic::getW()
{
	return (r/(2*L))*(motorD.getSpeedRadS() - motorE.getSpeedRadS());
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

void Kinematic::calibrateLineSensor(uint32_t iterations)
{
	lineSensor.calibrate(iterations);
	calibrationFinished = 1;
}

void Kinematic::updateLineAngle()
{
	lineSensorReading = lineSensor.read();
	distance = sqrt(xPos*xPos + yPos*yPos);
	if ((distance - lastDistance) > 0)
	{
		angle = atan2(lineSensorReading - lastLineSensorReading, distance - lastDistance);
		lastDistance = distance;
	}
	/*
	if ((sqrt(xPos*xPos + yPos*yPos) - lastDistance) >= 0.001)
	{
		angle = atan2(thisLoopLineRead - lastLineSensorReading, sqrt(xPos*xPos + yPos*yPos) - lastDistance);
		lastDistance = sqrt(xPos*xPos + yPos*yPos);
	}
	*/
	lastLineSensorReading = lineSensorReading;
}

float Kinematic::getLineAngle()
{
	return angle;
}

float Kinematic::getLinePosition()
{
	return lineSensorReading;
}



