#include "TIMER.h"

//This constructor configure the respective pin as Alternated function output (it's needed to use PWM in that pin)
//and after that enable the clock of the respective timer
Timer::Timer(TIM_TypeDef *TIM, TIM_CHANNELS channel, TIM_MODE_IO mode)
{
	SetTim(TIM);
	SetTIMChannel(channel);
	SetTIMMode(mode);
	
	//Enable the clock of the respective timer
	if (GetTim() == TIM1)			RCC->APB2ENR |= (1<<11);
	else if(GetTim() == TIM2)	RCC->APB1ENR |= (1<<0);
	else if(GetTim() == TIM3)	RCC->APB1ENR |= (1<<1);
	else if(GetTim() == TIM4)	RCC->APB1ENR |= (1<<2);
}


//-------------------------------SETTERS------------------------------------
void Timer::SetTim(TIM_TypeDef *TIM)
{
	this->TIM = TIM;
}
void Timer::SetTIMChannel(TIM_CHANNELS TIMChannel)
{
	this->TIMChannel = TIMChannel;
}
void Timer::SetTIMMode(TIM_MODE_IO TIMMode)
{
	this->TIMMode = TIMMode;
}
void Timer::SetTIMRemap(TIM_REMAP TIMRemap)
{
	this->TIMRemap = TIMRemap;
}

//-------------------------------GETTERS------------------------------------
TIM_TypeDef* Timer::GetTim()
{
	return (this->TIM);
}
TIM_CHANNELS Timer::GetTIMChannel()
{
	return (this->TIMChannel);
}

TIM_MODE_IO Timer::GetTIMMode()
{
	return (this->TIMMode);
}

TIM_REMAP Timer::GetTIMRemap(TIM_TypeDef *TIM)
{
	return (this->TIMRemap);
}
