#include "ENCODER.h"

//Declaration of the static variables
uint32_t Encoder::Overflowed_Ticks[NUMBER_OF_ENCODERS];
uint32_t Encoder::Ticks[NUMBER_OF_ENCODERS];
uint32_t Encoder::LastTicks[NUMBER_OF_ENCODERS];
uint32_t Encoder::Ticks_Time[NUMBER_OF_ENCODERS];
uint32_t Encoder::LastTicks_Time[NUMBER_OF_ENCODERS];
uint32_t Encoder::Speed[NUMBER_OF_ENCODERS];
TIM_TypeDef *Encoder::Encoder_Timers[NUMBER_OF_ENCODERS];
uint8_t Encoder::Number_of_Encoders;

void Encoder::Encoder_Initiallize()
{
	for(int i = 0; i<NUMBER_OF_ENCODERS; i++)
	{
		Encoder::Overflowed_Ticks[i] = 0;
		Encoder::Ticks[i] = 1;
		Encoder::LastTicks[i] = 0;
		Encoder::Ticks_Time[i] = 1;
		Encoder::LastTicks_Time[i] = 0;
		Encoder::Speed[i] = 0;
	}
	Encoder::Number_of_Encoders = 0;
}

void Encoder::Encoder_Handler(ENCODER_ENUM enc_num)
{
	Encoder::Ticks_Time[enc_num] = Timer::GetTime_usec();
		//this 500000* is to convert ticks/us in rpm
	Encoder::Speed[enc_num] = 500000*Ticks_till_int;
	Encoder::Speed[enc_num] = Encoder::Speed[enc_num]/(Encoder::Ticks_Time[enc_num] - Encoder::LastTicks_Time[enc_num]);
	Encoder::LastTicks_Time[enc_num] = Encoder::Ticks_Time[enc_num];
}

void Encoder::Encoder_Ticks_overflow(TIM_TypeDef *TIM)
{
	for(int i = 0; i<NUMBER_OF_ENCODERS; i++)
	{
		if(Encoder::Encoder_Timers[i] == TIM)
		{
			Encoder::Overflowed_Ticks[i] += AutoReaload_Ticks;
		}			
	}	
}

Encoder::Encoder(TIM_TypeDef *TIM)
{
	SetTim(TIM);
	ConfigEncoder();
}

void Encoder::ConfigEncoder()
{
	Encoder::Encoder_Timers[Number_of_Encoders] = GetTim();
	Encoder::Number_of_Encoders++;
	
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
	
	GetTim()->SR &= ~(1<<0);		//Clear Update interrupt flag
	GetTim()->SMCR |= (1<<1) | (1<<0);			//Encoder counting on both channels events
	GetTim()->ARR = AutoReaload_Ticks;									//In case there is an overflow, we know that it'll occur in a rounded number 
	GetTim()->CCMR1 |= (1<<0);							//IC1 is mapped on TI1
	GetTim()->CCMR1 |= (1<<8);							//IC2 is mapped on TI2	
	GetTim()->CCER |= (1<<1);								//invert the polarity, just because of the line follower.
//-----interrupt part-----------	
	GetTim()->EGR |= (1<<0);		//Update generation -> Generate an uptade of all configurations done before
	GetTim()->SR &= ~(1<<0);		//Clear Update interrupt flag
	GetTim()->DIER |= (1<<0);		//Enable the timer to generate a interrupt flag
	if (GetTim() == TIM1) NVIC->ISER[0] |= (1<<TIM1_UP_IRQn);			//Enable the interrupt in the NVIC
	else if (GetTim() == TIM2) NVIC->ISER[0] |= (1<<TIM2_IRQn);
	else if (GetTim() == TIM3) NVIC->ISER[0] |= (1<<TIM3_IRQn);
	else if (GetTim() == TIM4) NVIC->ISER[0] |= (1<<TIM4_IRQn);
//------------------------------
	GetTim()->CR1 |= (1<<0);								//Enable the counter
	
}

uint16_t Encoder::GetEncTicks()
{
	return GetTim()->CNT;
}

uint32_t Encoder::GetEncSpeed()
{
	for(int i = 0; i<NUMBER_OF_ENCODERS; i++)
	{
		if(Encoder::Encoder_Timers[i] == GetTim())
		{
			return Encoder::Speed[i];
		}			
	}
	return 0; //this case will never happens, but the copiller shows a warning, so it's here to avoid the warning
}

bool Encoder::GetEncDirection()
{
	return ((GetTim()->CR1) & (1<<4));
}

