#include "ENCODER.h"

Encoder *Encoder::encPtr[NUMBER_OF_ENCODERS];
bool Encoder::usedEncoders[NUMBER_OF_ENCODERS];

void Encoder::Encoder_Initiallize()
{
	for(int i = 0; i<NUMBER_OF_ENCODERS; i++)
	{
		Encoder::usedEncoders[i] = 0;
	}
}

void Encoder::Encoder_Handler(ENCODER_ENUM enc)
{
	Encoder::encPtr[enc]->Handler();
}

void Encoder::Encoder_Handler_by_Time()
{
	for (int i = 0; i < NUMBER_OF_ENCODERS; i++)
	{
		if (Encoder::usedEncoders[i] == 1)
		{
			if ((( Timer::GetTime_usec() - Encoder::encPtr[i]->LastTicks_Time) > Max_delay_Ticks_Time) && (Encoder::encPtr[i]->Speed != 0))
			{
				Encoder::encPtr[i]->LastTicks_Time = Timer::GetTime_usec();
				Encoder::encPtr[i]->Speed = 0;
			}	
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
	if 			(GetTim() == TIM1)	encoderNumber = Encoder_TIM1;
	else if (GetTim() == TIM2)	encoderNumber = Encoder_TIM2;
	else if (GetTim() == TIM3)	encoderNumber = Encoder_TIM3;
	else if (GetTim() == TIM4)	encoderNumber = Encoder_TIM4;
	Encoder::encPtr[encoderNumber] = this;
	Encoder::usedEncoders[encoderNumber] = 1;
	
	Ticks = 0;
	Ticks_Time = 1;
	LastTicks_Time = 0;
	Speed = 0;
	Last_Speed = 0;
	
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

uint32_t Encoder::getTicks()
{
	return Ticks + GetTim()->CNT;	
}

uint32_t Encoder::getTicksTime()
{
	return Ticks_Time;
}

uint32_t Encoder::getLastTicksTime()
{
	return LastTicks_Time;
}

float Encoder::getSpeed()
{
	return Speed;
}

float Encoder::getLastSpeed()
{
	return Last_Speed;
}

void Encoder::Handler()
{
	Ticks += Ticks_till_int;
	Ticks_Time = Timer::GetTime_usec();
	Speed = (500000*Ticks_till_int)/(Ticks_Time - LastTicks_Time);			//this 500000* is to convert ticks/us in rpm
	if (Last_Speed > 900)
	{
		if(Speed == 0)
		{
			Speed = Last_Speed;
		}
	}
	Last_Speed = Speed;
	LastTicks_Time = Ticks_Time;
}
