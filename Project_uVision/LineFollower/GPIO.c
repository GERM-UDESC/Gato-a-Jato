#include "GPIO.h"
#include "stdint.h"


//------------------------Config_pin-----------------------------------------------
void Config_pin(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mode)
{
	if (port == GPIOA)												//If GPIOA is the chosen one
		RCC->APB2ENR |= (1<<2);									//enable the clock of GPIO_A
	if (port == GPIOB)												//If GPIOB is the chosen one
		RCC->APB2ENR |= (1<<3);									//enable the clock of GPIO_B
	if (port == GPIOC)												//If GPIOB is the chosen one
		RCC->APB2ENR |= (1<<4);									//enable the clock of GPIO_C
	
	
	if (pinNumber >= 8)																//if pin number >= 8, we must use CRH
	{
		uint16_t pin_base = (pinNumber - 8)*4;					//Just converting the pin number to it respective address in the CRH
		switch (mode)
		{
			case OUTPUT:
				port->CRH |= ((1<<pin_base) | (1<<(pin_base+1)));				//Config mode 0 and 1 to high -> output max speed 50MHz
				port->CRH &= ~((1<<(pin_base+2)) | (1<<(pin_base+3)));	//config as push pull
				
			break;
			
			case INPUT:
												//it is the default
			
			break;
			
			default:
			break;
		}
	}
	else
	{
		uint16_t pin_base = (pinNumber)*4;					//Just converting the pin number to it respective address in the CRL
		switch (mode)
		{
			case OUTPUT:
				port->CRL |= ((1<<pin_base) | (1<<(pin_base+1)));	//Config mode 0 and 1 to high -> output max speed 50MHz
				port->CRL &= ~((1<<(pin_base+2)) | (1<<(pin_base+3)));//config as push pull
				
			break;
			
			case INPUT:
												//it is the default
			
			break;
			
			default:
			break;
		}
		
	}
		
}

//------------------------Write_pin-----------------------------------------------
void Write_pin(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t state)
{
	if (state == LOW)
		port->BSRR |= (1<<(pinNumber+16));							
	else
		port->BSRR |= (1<<(pinNumber));								//If the state is not LOW, I'll consider it as HIGH
}

//------------------------Toogle_pin-----------------------------------------------
void Toogle_pin(GPIO_TypeDef *port, uint32_t pinNumber)
{
	port->ODR ^=(1<<pinNumber);																						//^ means exclusive or
}

//------------------------Read_pin-------------------------------------------------
uint16_t Read_pin(GPIO_TypeDef *port, uint32_t pinNumber)
{
	uint16_t bit_value = port->ODR;																	
	
	return BIT_TEST(bit_value, pinNumber);
}

