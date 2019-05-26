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
}

void Kinematic::reset()
{
	motorD.reset();
	motorE.reset();
	xPos = 0;
	yPos = 0;
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

//void Kinematic::setRobotRefereceSpeed(float Vx, float Vy, float Vteta)
//{
//	vMotDref = (1/r)*(Vx*cos(getTeta()) + Vy*sin(getTeta()) + L*Vteta);
//	vMotEref = (1/r)*(Vx*cos(getTeta()) + Vy*sin(getTeta()) - L*Vteta);
//	
//	vRef = (r/(2))*(vMotDref + vMotEref);
//	wRef = (r/(2*L))*(vMotDref - vMotEref);
//	
//	motorD.Set_Speed(vMotDref);
//	motorE.Set_Speed(vMotEref);
//}

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
	
	float deltaDistance;
	deltaDistance = (motorD.getDeltaDistance() + motorE.getDeltaDistance())/2;
	xPos += deltaDistance*cos(getTeta());
	yPos += deltaDistance*sin(getTeta());
	
	posControl();
}

void Kinematic::posControl()
{
	Ew[k] = 0 - getLineAngle();
	Uw[k] = ((KPw*ts_w+2*KDw)*Ew[k] + (KPw*ts_w-2*KDw)*Ew[k-1] - ts_w*Uw[k-1])/ts_w;
	
	for (int i = 0; i < k; i++)
	{
		Uw[i] = Uw[i+1];
		Ew[i] = Ew[i+1];
	}
	
	setRobotSpeed(vRef, Uw[k]);
	
}

float Kinematic::getV()
{
	return (r/(2))*(motorD.getSpeedRadS() + motorE.getSpeedRadS());
}

float Kinematic::getW()
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

void Kinematic::calibrateLineSensor(uint32_t iterations)
{
	lineSensor.calibrate(iterations);
}

void Kinematic::updateLineAngle()
{
//	if ((sqrt(xPos*xPos + yPos*yPos) - lastDistance) != 0)
//	{
//		angle = atan(lineSensor.read() - lastLineSensorReading)/(sqrt(xPos*xPos + yPos*yPos) - lastDistance); //  arctg(deltaReading/deltaDistance)
//		lastLineSensorReading = lineSensor.read();
//		lastDistance = sqrt(xPos*xPos + yPos*yPos);
//	}
	float thisLoopLineRead = lineSensor.read();
	angle = atan2(thisLoopLineRead - lastLineSensorReading, sqrt(xPos*xPos + yPos*yPos) - lastDistance);
	lastLineSensorReading = thisLoopLineRead;
	lastDistance = sqrt(xPos*xPos + yPos*yPos);
}

float Kinematic::getLineAngle()
{
	return angle;
}




