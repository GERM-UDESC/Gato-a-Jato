#include "TIMER.h"

//This constructor configure the respective pin as Alternated function output (it's needed to use PWM in that pin)
//and after that enable the clock of the respective timer
Timer::Timer(TIM_TypeDef *TIM, TIM_CHANNELS channel, TIM_MODE_IO mode)
{
	this->TIM = TIM;
	this->channel = channel;
	this->mode = mode;
	
	//Enable the clock of the respective timer
	if (this->TIM == TIM1)			RCC->APB2ENR |= (1<<11);
	else if(this->TIM == TIM2)	RCC->APB1ENR |= (1<<0);
	else if(this->TIM == TIM3)	RCC->APB1ENR |= (1<<1);
	else if(this->TIM == TIM4)	RCC->APB1ENR |= (1<<2);	
}

//-------------------------------GETTERS------------------------------------
TIM_CHANNELS Timer::get_channel()
{
	return (this->channel);
}

TIM_MODE_IO Timer::get_mode()
{
	return (this->mode);
}
