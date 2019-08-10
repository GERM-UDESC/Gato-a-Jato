#include "FOLLOWING_CONTROLER.h"

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
		if(tetae > pi/4) tetae = pi/4;
		else if (tetae < -pi/4) tetae = -pi/4;
		ptController->controlRule();
	}
};

void Controller::controlRule()
{
	//kanayama_control();
	article_control();
	//fierro_control();
};

void Controller::kanayama_control()
{
	v = v_ref*cos(tetae) + Kx*xe;
	w = w_ref + v_ref*(Ky*ye + Kteta*sin(tetae));
	
	Robot.setSpeed(v, w);
}

void Controller::fierro_control()
{
	float v_read = Robot.getV();
	float w_read = Robot.getW();
	
	vc = v_ref*cos(tetae) + Kxk*xe;
	wc = w_ref + Kyk*v_ref*ye+Ktetak*v_ref*sin(tetae);

	xep = w_read*ye-v_read + v_ref*cos(tetae);
	yep = -w_read*xe + v_ref*sin(tetae);
	tetaep = w_ref - w_read;

	vcp = Kxk*xep - tetaep*v_ref*sin(tetae);
	wcp = Kyk*v_ref*yep + Ktetak*v_ref*cos(tetae)*tetaep;

	v = K4k*(vc - v_read) + vcp;
	w = K4k*(wc - w_read) + wcp;
	Robot.setSpeed(v, w);
}

void Controller::article_control()
{
	if ((tetae > 0.005) && (tetae < - 0.005))
	{
		w = K1a*tetae + K2a*ye*v_ref*sin(tetae)/tetae;
	}
	else
	{
		w = K1a*tetae + K2a*ye*v_ref;
	}
    
	Robot.setSpeed(v_ref, w);
}

void Controller::setSpeedRef(float vr, float wr)
{
	v_ref = vr;
	w_ref = wr;
}

void Controller::reset()
{
	Robot.reset();
	xe = 0;
	ye = 0;
	tetae = 0;
	v = 0;
	w = 0;
}

