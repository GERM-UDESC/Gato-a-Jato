#ifndef	GPIO_function

#include "Micro.h"

#define HIGH	1
#define	LOW		0


//By Daniel mass:    //I took these functions because they could be usefull
#define BIT_TEST(mem,bit)   ((mem)&(1<<(bit))) //This macro is used to perform test on bit of the data
#define BIT_SET(mem,bit)    ((mem)|=(1<<(bit))) //This macro is used to set the bit of the data
#define BIT_CLR(mem,bit)    ((mem)&=~(1<<(bit))) //This macro is used to clear the bit of the data
#define BIT_TOGGLE(mem,bit) ((mem)^=(1<<(bit))) //This macro is used to toggle the bit of the data


typedef enum{						//I put in an enum because it will be easier to implement other modes in the future
	INPUT = 0,						//will be it by default
	OUTPUT,								//by default, output speed will be 50MHz and output will be push-pull
	ALTERNATED_FUNCTION		//don't know how to use yet
}GPIO_modes;

//Function to config the pin
void Config_pin(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mode);		//Here mode can be any of those put into GPIO_modes above

//Function to write/read to the pin port
void Write_pin(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t state);		//Write HIGH or LOW into a pin
void Toogle_pin(GPIO_TypeDef *port, uint32_t pinNumber);									//Toogle pin	
uint16_t Read_pin(GPIO_TypeDef *port, uint32_t pinNumber);								//Return high or low acording to the readed value


#endif
