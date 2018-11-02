#include "TIMER.h"

//This constructor configure the respective pin as Alternated function output (it's needed to use PWM in that pin)
//and after that enable the clock of the respective timer
Timer::Timer(TIM_TypeDef *TIM, TIM_CHANNELS channel, TIM_MODE mode)
{
	SetTim(TIM);
	SetTIMChannel(channel);
	SetTIMMode(mode);
	
	TimerInit();
}

Timer::Timer(TIM_TypeDef *TIM, TIM_MODE mode)
{
	SetTim(TIM);
	SetTIMMode(mode);
	
	TimerInit();
}

void Timer::TimerInit()
{
	//Enable the clock of the respective timer
	if (GetTim() == TIM1)			RCC->APB2ENR |= (1<<11);
	else if(GetTim() == TIM2)	RCC->APB1ENR |= (1<<0);
	else if(GetTim() == TIM3)	RCC->APB1ENR |= (1<<1);
	else if(GetTim() == TIM4)	RCC->APB1ENR |= (1<<2);
	
	switch (GetTIMMode())
	{
		case COUNTER:
			
			GetTim()->SR &= ~(1<<0);		//Clear Update interrupt flag
			
			GetTim()->PSC = 720; 				//Configure the preescaler to make the count frequency 1MHz
	
			GetTim()->ARR = 65000;			//number of clocks to generate an flag/interrupt
			
			GetTim()->EGR |= (1<<0);		//Update generation -> Generate an uptade of all configurations done before
			
			GetTim()->SR &= ~(1<<0);		//Clear Update interrupt flag
			
			GetTim()->DIER |= (1<<0);		//Enable interrupts
			
			NVIC->ISER[0] |= (1<<TIM1_UP_IRQn);
			
			GetTim()->CR1 |= (1<<0);		//Enable the counter
		
		break;
		
		default:
		break;
	}
	
}

void Timer::InterrupTime(uint16_t time)
{
	GetTim()->ARR = time;
}

void Timer::ClearInterruptFlag()
{
	GetTim()->SR &= ~(1<<0);		//Clear Update interrupt flag
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
void Timer::SetTIMMode(TIM_MODE TIMMode)
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
TIM_MODE Timer::GetTIMMode()
{
	return (this->TIMMode);
}


