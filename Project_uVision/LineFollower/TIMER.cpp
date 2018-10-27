#include "TIMER.h"

//This constructor configure the respective pin as Alternated function output (it's needed to use PWM in that pin)
//and after that enable the clock of the respective timer
Timer::Timer(TIM_TypeDef *TIM, TIM_CHANNELS channel, TIM_MODE_IO mode)
{
	SetTimer(TIM);
	SetChannel(channel);
	SetMode(mode);
	
	//Enable the clock of the respective timer
	if (GetTimer() == TIM1)			RCC->APB2ENR |= (1<<11);
	else if(GetTimer() == TIM2)	RCC->APB1ENR |= (1<<0);
	else if(GetTimer() == TIM3)	RCC->APB1ENR |= (1<<1);
	else if(GetTimer() == TIM4)	RCC->APB1ENR |= (1<<2);
}


//-------------------------------SETTERS------------------------------------
void Timer::SetTimer(TIM_TypeDef *TIM)
{
	this->TIM = TIM;
}
void Timer::SetChannel(TIM_CHANNELS channel)
{
	this->channel = channel;
}
void Timer::SetMode(TIM_MODE_IO mode)
{
	this->mode = mode;
}

//-------------------------------GETTERS------------------------------------
TIM_TypeDef* Timer::GetTimer()
{
	return this->TIM;
}
TIM_CHANNELS Timer::get_channel()
{
	return (this->channel);
}

TIM_MODE_IO Timer::get_mode()
{
	return (this->mode);
}
