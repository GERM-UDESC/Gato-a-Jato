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
}GPIO_modes;

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
}PIN_numbers;

//Enumeration of pull_up/pull_down
typedef enum{				//This values should be written in the ODR register according to your need
	PULL_DOWN = 0,
	PULL_UP = 1,
}PU_PD_enum;


//--------------------------------------------CLASS------------------------------------------------------


class GPIO
{
		private:
		//Atributes
		GPIO_TypeDef *port;					
		PIN_numbers pinNumber;
		GPIO_modes mode;
		PU_PD_enum PU_PD;
		bool state;							//in case it's output


		protected:
		//Setters for child classes
		void SetPort(GPIO_TypeDef *port);
		void SetPinNumber(PIN_numbers pinNumber);
		void SetMode(GPIO_modes mode);
		
		//Methods
		void ConfigPin();
			
		public:
		//Constructors
		GPIO(){};
		GPIO(GPIO_TypeDef *port, PIN_numbers pinNumber, GPIO_modes mode);
		
		//Getters
		GPIO_TypeDef* GetPort();
		PIN_numbers GetPinNumber();
		GPIO_modes GetMode();
		PU_PD_enum GetPuPd();

		//Public Methods
		void Config_PU_PD(PU_PD_enum PU_PD);	//By defaul, PD is choosen, this functions allows the user to change to PU/PD;
		void Write_pin(bool state);
		void Toogle_pin();
		bool Read_pin();

		
};
#endif

