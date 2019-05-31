#include "KANAYAMA_CONTROLER.h"

Controller *Controller::ptController;

Controller::Controller(Kinematic Robot): Robot(&Robot)
{
	Controller::ptController = this;
};

void Controller::HandlerByTime()
{
	Controller::ptController->Handler();	
};

void Controller::Handler()
{
	if (Robot.calibrationFinished == 1)
	{
		Robot.updateLineAngle();
		xe = 0;
		ye = Robot.getLinePosition();
		tetae = Robot.getLineAngle();
		if(tetae > pi/6) tetae = pi/6;
		else if (tetae < -pi/6) tetae = -pi/6;
//		tetae = 0;
	}
};

void Controller::controlRule()
{
	V = v_ref*cos(tetae) + Kx*xe;
	w = w_ref + v_ref*(Ky*ye + Kteta*sin(tetae));
	
	Robot.setSpeed(V, w);
};

void Controller::reset()
{
	Robot.reset();
	xe = 0;
	ye = 0;
	tetae = 0;
	V = 0;
	w = 0;
}

