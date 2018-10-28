#include "ENCODER.h"

Encoder::Encoder(TIM_TypeDef *TIM)
{
	SetTim(TIM);
	ConfigEncoder();
}

void Encoder::ConfigEncoder()
{
	//Enable the clock of the respective timer
	if (GetTim() == TIM1)			RCC->APB2ENR |= (1<<11);
	else if(GetTim() == TIM2)	RCC->APB1ENR |= (1<<0);
	else if(GetTim() == TIM3)	RCC->APB1ENR |= (1<<1);
	else if(GetTim() == TIM4)	RCC->APB1ENR |= (1<<2);
	
	SetGPIOMode(INPUT_FLOATING);
	
	if (GetTim() == TIM1)
	{
		SetGPIOPort(GPIOA);
		SetGPIOPinNumber(PIN8);
		ConfigGPIOPin();
		SetGPIOPort(GPIOA);
		SetGPIOPinNumber(PIN9);
		ConfigGPIOPin();
	}
	else if (GetTim() == TIM2)
	{
		SetGPIOPort(GPIOA);
		SetGPIOPinNumber(PIN0);
		ConfigGPIOPin();
		SetGPIOPort(GPIOA);
		SetGPIOPinNumber(PIN1);
		ConfigGPIOPin();
	}
	else if (GetTim() == TIM3)
	{
		SetGPIOPort(GPIOA);
		SetGPIOPinNumber(PIN6);
		ConfigGPIOPin();
		SetGPIOPort(GPIOA);
		SetGPIOPinNumber(PIN7);
		ConfigGPIOPin();
	}
	else if (GetTim() == TIM4)
	{
		SetGPIOPort(GPIOB);
		SetGPIOPinNumber(PIN6);
		ConfigGPIOPin();
		SetGPIOPort(GPIOB);
		SetGPIOPinNumber(PIN7);
		ConfigGPIOPin();
	}
	
	GetTim()->SMCR |= (1<<1) | (1<<0);			//Encoder counting on both channels events
	GetTim()->ARR = 36000;									//In case there is an overflow, we know that it'll occur in a rounded number 
	GetTim()->CCMR1 |= (1<<0);							//IC1 is mapped on TI1
	GetTim()->CCMR1 |= (1<<8);							//IC2 is mapped on TI2		
	GetTim()->CR1 |= (1<<0);								//Enable the counter
}

uint16_t Encoder::GetEncTicks()
{
	return GetTim()->CNT;
}

bool Encoder::GetEncDirection()
{
	return ((GetTim()->CR1) & (1<<4));
}

