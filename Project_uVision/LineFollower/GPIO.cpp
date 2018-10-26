#include "GPIO.h"
#include "stdint.h"


//Construtores
GPIO::GPIO(GPIO_TypeDef *port, PIN_numbers pinNumber, GPIO_modes mode)
{
		this->port = port;					
		this->pinNumber = pinNumber;
		this->mode = mode;
	
		this->ConfigPin();
		this->Config_PU_PD(PULL_DOWN);		//Config PULL_DOWN as default
}


//------------------------Config_pin-----------------------------------------------
void GPIO::ConfigPin()
{
	//Enable the clock of the chosen port
	if (this->port == GPIOA)				RCC->APB2ENR |= (1<<2);									
	else if (this->port == GPIOB)		RCC->APB2ENR |= (1<<3);									
	else if (this->port == GPIOC)		RCC->APB2ENR |= (1<<4);
	else if (this->port == GPIOD)		RCC->APB2ENR |= (1<<5);
	else if (this->port == GPIOE)		RCC->APB2ENR |= (1<<6);
	else if (this->port == GPIOF)		RCC->APB2ENR |= (1<<7);
	else if (this->port == GPIOG)		RCC->APB2ENR |= (1<<8);	
	
	//Configure the pin
	if ((this->pinNumber) >= PIN8)							//if pin number >= 8, we must use CRH
	{
		//Just converting the pin number to it respective address in the CRH
		uint16_t pin_base = ((this->pinNumber) - 8)*4;					
		
		//put all bits related to the pin to 0
		this->port->CRH &= ~((0xF)<<(pin_base));				
		this->port->ODR &= ~(1<<(this->pinNumber));		//this line serves to put the output to 0 or to configure the input as pull down as default
		
		//configure the pin
		this->port->CRH |= ((this->mode)<<(pin_base));
	}
	else
	{
		//Just converting the pin number to it respective address in the CRL
		uint16_t pin_base = (this->pinNumber)*4;					
		
		//put all bits related to the pin to 0
		this->port->CRL &= ~((0xF)<<(pin_base));				
		this->port->ODR &= ~(1<<(this->pinNumber));		//this line serves to put the output to 0 or to configure the input as pull down as default
		
		//configure the pin
		this->port->CRL |= ((this->mode)<<(pin_base));
	}
		
}


//------------------------PU_PD--------------------------------------------------
void GPIO::Config_PU_PD(PU_PD_enum PU_PD)
{
	this->PU_PD = PU_PD;
	
	if ((this->PU_PD) == PULL_UP)
		this->port->ODR |= (1<<(this->pinNumber));
	else
		this->port->ODR &= ~(1<<(this->pinNumber));
}

//------------------------Write_pin-----------------------------------------------
void GPIO::Write_pin(bool state)
{
	this->state = state;
	if (this->state == LOW)
		this->port->BSRR |= (1<<((this->pinNumber)+16));							
	else
		this->port->BSRR |= (1<<(this->pinNumber));								//If the state is not LOW, I'll consider it as HIGH
}

//------------------------Toogle_pin-----------------------------------------------
void GPIO::Toogle_pin()
{
	this->port->ODR ^=(1<<(this->pinNumber));																						//^ means exclusive or
}

//------------------------Read_pin-------------------------------------------------
bool GPIO::Read_pin()
{
	return (this->port->IDR) & (1<<(this->pinNumber));
}

//Setters
void GPIO::SetPort(GPIO_TypeDef *port)
{
	this->port = port;
}

void GPIO::SetPinNumber(PIN_numbers pinNumber)
{
	this->pinNumber = pinNumber;
}
void GPIO::SetMode(GPIO_modes mode)
{
	this->mode = mode;
}

//Getters
GPIO_TypeDef* GPIO::GetPort()
{
	return this->port;
}
PIN_numbers GPIO::GetPinNumber()
{
	return this->pinNumber;
}
GPIO_modes GPIO::GetMode()
{
	return this->mode;
}
PU_PD_enum GPIO::GetPuPd()
{
	return this->PU_PD;
}
