#ifndef	GPIO_H
#define GPIO_H
#include "Micro.h"

#define HIGH	1
#define	LOW		0

//--------------------------------------------ENUMs------------------------------------------------------


//All possibles operation modes are enumerated here
typedef enum{
	INPUT_ANALOG = 0x0,
	GP_OUTPUT_PUSH_PULL_10MHZ = 0x1,
	GP_OUTPUT_PUSH_PULL_2MHZ = 0x2,
	GP_OUTPUT_PUSH_PULL_50MHZ = 0x3,
	INPUT_FLOATING = 0x4,
	GP_OUTPUT_OPEN_DRAIN_10MHZ = 0x5,
	GP_OUTPUT_OPEN_DRAIN_2MHZ = 0x6,
	GP_OUTPUT_OPEN_DRAIN_50MHZ = 0x7,
	INPUT_PULL_UP_DOWN = 0x8,						//to select if it must be PU or PD, we must use the ODR register
	AF_OUTPUT_PUSH_PULL_10MHZ = 0x9,
	AF_OUTPUT_PUSH_PULL_2MHZ = 0xA,
	AF_OUTPUT_PUSH_PULL_50MHZ = 0xB,
	AF_OUTPUT_OPEN_DRAIN_10MHZ = 0xD,
	AF_OUTPUT_OPEN_DRAIN_2MHZ = 0xE,
	AF_OUTPUT_OPEN_DRAIN_50MHZ = 0xF,
}GPIO_MODES;

//All possibles 16 pins (0 - 15) are enumerated here
typedef enum{		
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15,
	NUMBER_OF_PINS,	//NUMBER_OF_PINS == 16,
}PIN_NUMBERS;

//Enumeration of pull_up/pull_down
typedef enum{				//This values should be written in the ODR register according to your need
	PULL_DOWN = 0,
	PULL_UP = 1,
}PU_PD_ENUM;


//---------------------------Hardware Abstraction Layers-----------------------------------------
typedef enum{
	PA0,
	PA1,
	PA2,
	PA3,
	PA4,
	PA5,
	PA6,
	PA7,
	PA8,
	PA9,
	PA10,
	PA11,
	PA12,
	PA15,
	PB0,
	PB1,
	PB3,
	PB4,
	PB5,
	PB6,
	PB7,
	PB8,
	PB9,
	PB10,
	PB11,
	PB12,
	PB13,
	PB14,
	PB15,
	PC13,
	PC14,
	PC15,
	NUM_OF_IOs,	
}GPIO_IO_ENUM;

typedef struct{
	GPIO_TypeDef *PortTest;
	PIN_NUMBERS pinNumberTest;
}GPIO_STRUCT;

//typedef enum{
//	PIN_NOT_USED,
//	PIN_IS_USED,
//}USED_PINS_ENUM;


//--------------------------------------------CLASS------------------------------------------------------

class GPIO
{
		private:
		//Atributes
		GPIO_TypeDef *GPIOPort;					
		PIN_NUMBERS GPIOPinNumber;
		
		//GPIO_STRUCT GPIO_PortPin;		//Save the port and pin
		GPIO_MODES GPIOMode;				//Save the mode
		PU_PD_ENUM PU_PD;
		bool GPIOState;							//in case it's output
		


		protected:
		//Setters for child classes
		void SetGPIOPort(GPIO_TypeDef *GPIOPort);
		void SetGPIOPinNumber(PIN_NUMBERS GPIOPinNumber);
		void SetGPIOMode(GPIO_MODES GPIOMode);
		
		//Methods
		void ConfigGPIOPin();
			
		public:
		//Constructors
		GPIO(){};
		GPIO(GPIO_IO_ENUM IO_Pin, GPIO_MODES GPIOMode);
		GPIO(GPIO_TypeDef *GPIOPort, PIN_NUMBERS GPIOPinNumber, GPIO_MODES GPIOMode);
		
		//Getters
		GPIO_TypeDef* GetGPIOPort();
		PIN_NUMBERS GetGPIOPinNumber();
		GPIO_MODES GetGPIOMode();
		PU_PD_ENUM GetGPIOPuPd();
		bool GetGPIOState();

		//Public Methods
		void Config_PU_PD(PU_PD_ENUM PU_PD);	//By defaul, PD is choosen, this functions allows the user to change to PU/PD;
		void digitalWrite(bool GPIOState);
		void tooglePin();
		bool digitalRead();
};
#endif

