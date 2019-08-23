	#ifndef SERIAL_COMMUNICATION_H
	#define SERIAL_COMMUNICATION_H
	
	#include "FOLLOWING_CONTROLER.h"
	#include "USART.h"
	
	#define bitsToSend 2500
	#define sendingTime bitsToSend*Time_between_int/1000000
		
	typedef enum{
		stop = 0,
		start = 1,
		sendV_W = 2,
		sendV_Wcontrol = 3,
		sendMotorsSpeed = 4,
	}COMMANDS;
	
	class Communication
	{
		private: 
		Controller *LineFollower;
		USART *Serial;
		
		COMMANDS command{start};
		float temporary[4];
		
		void doCommand();
		
		public:
		Communication(Controller *LineFollower_, USART *Serial_);
		
		void waitForCommand();
		void verifyCommand();
		
	};
	
	
	
	#endif