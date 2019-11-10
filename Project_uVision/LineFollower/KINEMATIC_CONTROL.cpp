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
	xPosSensor = 0;
	yPosSensor = 0;
	for (int i = 0; i < (angleFilterOrder); i++)
	{
		angle[i] = 0;
	};
	lineSensorReading = 0;
	lastLineSensorReading = 0;
	distance = 0;
	deltaDistance = 0;
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
	
	this->deltaDistance = (motorD.getDeltaDistance() + motorE.getDeltaDistance())/2;
	xPos += this->deltaDistance*cos(getTeta())*distanceCorrection;
	yPos += this->deltaDistance*sin(getTeta())*distanceCorrection;
	xPosSensor = xPos + comprimento*cos(getTeta());
	yPosSensor = yPos + comprimento*sin(getTeta());
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
	return xPosSensor;		
}

float	Kinematic::getY()
{
	return yPosSensor;		
}

float Kinematic::getTeta()
{
	return angleCorrection*(r/(2*L))*(motorD.getTeta() - motorE.getTeta());	
}

void Kinematic::calibrateLineSensor(uint32_t iterations)
{
	lineSensor.calibrate(iterations);
	calibrationFinished = 1;
}

void Kinematic::updateLineReading()
{
	lineSensorReading = lineSensor.read();
	
	for (int i = 0; i < (angleFilterOrder-1); i++)
	{
		angle[i] = angle[i+1];
	};
	
	if ((this->deltaDistance)!= 0)
	{
		angle[angleFilterOrder-1] = atan2(lineSensorReading - lastLineSensorReading, this->deltaDistance);
	}	
		
//	if ((this->deltaDistance)!= 0)
//	{
//		angle[angleFilterOrder-1] = asin((lineSensorReading - lastLineSensorReading)/(this->deltaDistance));
//	}	
//	
	filteredAngle = 0;
	for (int i = 0; i < (angleFilterOrder); i++)
	{
		filteredAngle += angle[i];
	};
	filteredAngle = filteredAngle/angleFilterOrder;
	
	lastLineSensorReading = lineSensorReading;
//	xPos = 0;
//	yPos = 0;
}

float Kinematic::getLineAngle()
{
	return filteredAngle;
}

float Kinematic::getLinePosition()
{
	return lineSensorReading;
}

float Kinematic::getLineAngleNotFiltered()
{
	return angle[angleFilterOrder-1];
}



