#include "SERIAL_COMMUNICATION.h"

Communication::Communication(Controller *LineFollower_, USART *Serial_)
{
	LineFollower = LineFollower_;
	Serial = Serial_;
};

void Communication::doCommand()
{
	switch (command)
	{
		case start:
			LineFollower->start(1, 0);
		break;
		
		case stop:
			LineFollower->stop();
		break;
		
		case sendV_W:
			temporary[0] = LineFollower->Robot.getV();
			temporary[1] = LineFollower->Robot.getW();
			Serial->sendFloat(&temporary[0]);
			Serial->sendFloat(&temporary[1]);
		break;
		
		case sendV_Wcontrol:
			temporary[0] = LineFollower->getVcontrol();
			temporary[1] = LineFollower->getWcontrol();
			Serial->sendFloat(&temporary[0]);
			Serial->sendFloat(&temporary[1]);
		break;
		
		case sendMotorsSpeed:
			temporary[0] = LineFollower->Robot.motorD.Get_Speed();
			temporary[1] = LineFollower->Robot.motorE.Get_Speed();
			Serial->sendFloat(&temporary[0]);
			Serial->sendFloat(&temporary[1]);
		break;
		
	};
};

void Communication::waitForCommand()
{
	command = (COMMANDS)Serial->Receive();
	doCommand();
};

void Communication::verifyCommand()
{
	if (Serial->Available())
	{
		command = (COMMANDS)Serial->Receive();
		doCommand();
	}
};




