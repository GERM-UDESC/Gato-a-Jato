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
			//do nothing
		break;
		
		case end:
			//do nothing
		break;
		
		case sendV:
			temporary = LineFollower->Robot.getV();
			Serial->sendFloat(&temporary);
		break;
		
		case sendw:
			temporary = LineFollower->Robot.getW();
			Serial->sendFloat(&temporary);
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




