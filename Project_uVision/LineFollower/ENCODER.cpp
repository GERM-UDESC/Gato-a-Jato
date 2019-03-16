#include "ENCODER.h"

//Declaration of the static variables
uint32_t Encoder::Ticks[NUMBER_OF_ENCODERS];
uint32_t Encoder::Ticks_Time[NUMBER_OF_ENCODERS];
uint32_t Encoder::LastTicks_Time[NUMBER_OF_ENCODERS];
float Encoder::Speed[NUMBER_OF_ENCODERS];
float Encoder::Last_Speed[NUMBER_OF_ENCODERS];

uint8_t enc_num = 0;

void Encoder::Encoder_Initiallize()
{
	for(int i = 0; i<NUMBER_OF_ENCODERS; i++)
	{
		Encoder::Ticks[i] = 0;
		Encoder::Ticks_Time[i] = 1;
		Encoder::LastTicks_Time[i] = 0;
		Encoder::Speed[i] = 0;
		Encoder::Last_Speed[i] = 0;
	}
}

void Encoder::Encoder_Handler(TIM_TypeDef *TIMER)
{
	//uint8_t enc_num = 0; Passar como global
	if (TIMER == TIM1) enc_num = 0;
	else if (TIMER == TIM2) enc_num = 1;
	else if (TIMER == TIM3) enc_num = 2;
	else if (TIMER == TIM4) enc_num = 3;
	
	Encoder::Ticks[enc_num] += Ticks_till_int;
	Encoder::Ticks_Time[enc_num] = Timer::GetTime_usec();
	Encoder::Speed[enc_num] = (500000*Ticks_till_int)/(Encoder::Ticks_Time[enc_num] - Encoder::LastTicks_Time[enc_num]);			//this 500000* is to convert ticks/us in rpm
	if (Encoder::Last_Speed[enc_num] > 900)
	{
		if(Encoder::Speed[enc_num] == 0)
		{
			Encoder::Speed[enc_num] = Encoder::Last_Speed[enc_num];
		}
	}
//	{
//		if (((Encoder::Speed[enc_num] - Encoder::Last_Speed[enc_num]) > Max_speed_variation) 
//			|| ((Encoder::Speed[enc_num] - Encoder::Last_Speed[enc_num]) < -Max_speed_variation))	//verify if its noise
//		{
//			Encoder::Speed[enc_num] = Encoder::Last_Speed[enc_num];	//keep the last speed
//		}
//		else if(Encoder::Speed[enc_num] == 0)
//		{
//			Encoder::Speed[enc_num] = Encoder::Last_Speed[enc_num];
//		}
//	}
	Encoder::Last_Speed[enc_num] = Encoder::Speed[enc_num];
	Encoder::LastTicks_Time[enc_num] = Encoder::Ticks_Time[enc_num];
}

void Encoder::Encoder_Handler_by_Time()
{
	for (int i = 0; i < NUMBER_OF_ENCODERS; i++)
	{
		if ((( Timer::GetTime_usec() - Encoder::LastTicks_Time[i]) > Max_delay_Ticks_Time) && (Encoder::Speed[i] != 0))
		{
			Encoder::LastTicks_Time[i] = Timer::GetTime_usec();
			Encoder::Speed[i] = 0;
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
	if (GetTim() == TIM1) return Encoder::Ticks[Encoder_TIM1];
	else if (GetTim() == TIM2) return Encoder::Ticks[Encoder_TIM2];
	else if (GetTim() == TIM3) return Encoder::Ticks[Encoder_TIM3];
	else if (GetTim() == TIM4) return Encoder::Ticks[Encoder_TIM4];
	return 0;	// this case should never happens
}

float Encoder::GetEncSpeed()
{
	if (GetTim() == TIM1) return Encoder::Speed[Encoder_TIM1];
	else if (GetTim() == TIM2) return Encoder::Speed[Encoder_TIM2];
	else if (GetTim() == TIM3) return Encoder::Speed[Encoder_TIM3];
	else if (GetTim() == TIM4) return Encoder::Speed[Encoder_TIM4];
	return 0;	// this case should never happens
}


void TIM1_UP_IRQHandler()
{
	TIM1->SR &= ~(1<<0);
	Encoder::Encoder_Handler(TIM1);
};

//void TIM2_IRQHandler()						//this timer is being used as time base for the system
//{
//	TIM2->SR &= ~(1<<0);
//	Encoder::Encoder_Handler(TIM2);
//};

void TIM3_IRQHandler()
{
	TIM3->SR &= ~(1<<0);
	Encoder::Encoder_Handler(TIM3);
};

void TIM4_IRQHandler()
{
	TIM4->SR &= ~(1<<0);
	Encoder::Encoder_Handler(TIM4);
};
