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
	

	
	if (GetTim() == TIM1)
	{
		EncCH1.SetGPIOPortPin(PA8);
		EncCH2.SetGPIOPortPin(PA9);
	}
	else if (GetTim() == TIM2)
	{
		EncCH1.SetGPIOPortPin(PA0);
		EncCH2.SetGPIOPortPin(PA1);
	}
	else if (GetTim() == TIM3)
	{
		EncCH1.SetGPIOPortPin(PA6);
		EncCH2.SetGPIOPortPin(PA7);
	}
	else if (GetTim() == TIM4)
	{
		EncCH1.SetGPIOPortPin(PB6);
		EncCH2.SetGPIOPortPin(PB7);
	}
	
	EncCH1.SetGPIOMode(INPUT_FLOATING);
	EncCH2.SetGPIOMode(INPUT_FLOATING);
	
	EncCH1.ConfigGPIOPin();
	EncCH2.ConfigGPIOPin();
	
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

