	#ifndef SERIAL_COMMUNICATION_H
	#define SERIAL_COMMUNICATION_H
	
	#include "FOLLOWING_CONTROLER.h"
	#include "USART.h"
	
	#define samplingTime 10
	#define bitsToSend (samplingTime*1000000)/(Time_between_int)
	#define sendingTime bitsToSend*Time_between_int/1000000
		
//I tried to do with enum, to make the code better, but there was some problem that I couldn't find, so I've made with define
//	typedef enum{
//		stop = 0,
//		start = 1,
//		sendV_W = 2,
//		sendV_Wcontrol = 3,
//		sendMotorsSpeed = 4,
//	}COMMANDS;

//List of communication commands:
#define robotStop 0
#define robotRun 1
#define	sendV_W 2
#define	sendV_Wcontrol 3
#define sendV_W_and_V_Wcontrol 4
#define sendLineReading 5
#define	sendMotorsSpeed 6
#define	sendMotorsSpeedAndControl 7
#define	sendMotorsSpeedControlAndErrors 8

	class Communication
	{
		private: 
		static Communication *ptCommunication;
		void Handler();	
		
		Controller *LineFollower;
		USART *Serial;
		
		uint16_t counter{0};
		float temporary[6];
		
		void doCommand();
		
		public:
		Communication(Controller *LineFollower_, USART *Serial_);
		
		static void HandlerByTime();
		
		void waitForCommand();
		void verifyCommand();
		
		uint8_t command{robotStop};
	};
	
	
	
	#endif