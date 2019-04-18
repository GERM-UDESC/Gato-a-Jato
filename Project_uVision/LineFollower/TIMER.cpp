#include "TIMER.h"

TIM_REMAP Timer::TIM1Remap;
TIM_REMAP Timer::TIM2Remap;
TIM_REMAP Timer::TIM3Remap;
TIM_REMAP Timer::TIM4Remap;
uint32_t Timer::time_in_usec;
TIM_TypeDef *Timer::TIM_Timer_Counter;

void Timer::Timer_Initiallize()				//Initiallize all timer's static variables
{
	Timer::TIM1Remap = NO_REMAP;
  Timer::TIM2Remap = NO_REMAP;
  Timer::TIM3Remap = NO_REMAP;
  Timer::TIM4Remap = NO_REMAP;
  Timer::time_in_usec = 0;
}

void Timer::Timer_Handler()
{
	time_in_usec += Time_between_int;
}

uint32_t Timer::GetTime_usec()
{
	return (time_in_usec + Timer::TIM_Timer_Counter->CNT);
}

void Timer::delay(uint32_t delayTime_usec)
{
	uint32_t initTime = Timer::GetTime_usec();
	while((Timer::GetTime_usec() - initTime) < delayTime_usec);
}

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
			
			Timer::TIM_Timer_Counter = GetTim();
			
			GetTim()->SR &= ~(1<<0);		//Clear Update interrupt flag
			
			GetTim()->PSC = Prescale; 				//Configure the preescaler to make the count frequency 1MHz
	
			GetTim()->ARR = AutoReload_Counter;				//number of clocks to generate an flag/interrupt
			
			GetTim()->EGR |= (1<<0);		//Update generation -> Generate an uptade of all configurations done before
			
			GetTim()->SR &= ~(1<<0);		//Clear Update interrupt flag
			
			GetTim()->DIER |= (1<<0);		//Enable the timer to generate a interrupt flag
			
			if (GetTim() == TIM1) NVIC->ISER[0] |= (1<<TIM1_UP_IRQn);			//Enable the interrupt in the NVIC
			else if (GetTim() == TIM2) NVIC->ISER[0] |= (1<<TIM2_IRQn);
			else if (GetTim() == TIM3) NVIC->ISER[0] |= (1<<TIM3_IRQn);
			else if (GetTim() == TIM4) NVIC->ISER[0] |= (1<<TIM4_IRQn);
		
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
	if 			(GetTim() == TIM1)	Timer::TIM1Remap = TIMRemap;
	else if (GetTim() == TIM2)	Timer::TIM2Remap = TIMRemap;
	else if (GetTim() == TIM3)	Timer::TIM3Remap = TIMRemap;
	else if (GetTim() == TIM4)	Timer::TIM4Remap = TIMRemap;
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
TIM_REMAP Timer::GetTIMRemap()
{
	if 			(GetTim() == TIM1)	return	Timer::TIM1Remap;
	else if (GetTim() == TIM2)	return	Timer::TIM2Remap;
	else if (GetTim() == TIM3)	return	Timer::TIM3Remap;
	else if (GetTim() == TIM4)	return	Timer::TIM4Remap;
	return NO_REMAP;		//this line will never hapenns, but the compiler is shows a warning if I don't put this
}


