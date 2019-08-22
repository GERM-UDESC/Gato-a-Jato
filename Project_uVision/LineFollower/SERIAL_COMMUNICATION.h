	#ifndef SERIAL_COMMUNICATION_H
	#define SERIAL_COMMUNICATION_H
	
	#include "FOLLOWING_CONTROLER.h"
	#include "USART.h"
	
	#define bitsToSend 2500
	#define sendingTime bitsToSend*Time_between_int/1000000
		
	typedef enum{
		start = 0,
		end = 1,
		sendV = 2,
		sendw = 3,
		sendVcontrol = 4,
		sendWcontrol = 5,
	}COMMANDS;
	
	class Communication
	{
		private: 
		Controller *LineFollower;
		USART *Serial;
		
		COMMANDS command{start};
		float temporary;
		
		void doCommand();
		
		public:
		Communication(Controller *LineFollower_, USART *Serial_);
		
		void waitForCommand();
		void verifyCommand();
		
	};
	
	
	
	#endif