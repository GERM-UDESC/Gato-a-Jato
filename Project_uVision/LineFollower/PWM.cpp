#include "PWM.h"

//******************************************************************************************************************************

PWM::PWM(TIM_TypeDef *TIM, TIM_CHANNELS channel, TIM_REMAP remap) : Timer(TIM, channel, PWM_MODE)		//Timer Constructor
{	
	this->remap = remap;
	
	ConfigPWMPin();
	PWMInit();
}

//******************************************************************************************************************************

void PWM::ConfigPWMPin()	
{
	//Remap will make no efect at Timer1
	if (this->TIM == TIM1) 
	{
		switch (get_channel())
		{
			case CH1:
				GPIO(GPIOA, PIN8, AF_OUTPUT_PUSH_PULL_2MHZ);
			break;
			case CH2:
				GPIO(GPIOA, PIN9, AF_OUTPUT_PUSH_PULL_2MHZ);
			break;
			case CH3:
				GPIO(GPIOA, PIN10, AF_OUTPUT_PUSH_PULL_2MHZ);
			break;
			case CH4:
				GPIO(GPIOA, PIN11, AF_OUTPUT_PUSH_PULL_2MHZ);
			break;		
		}
	}
	
	if (this->TIM == TIM2) 
	{		
		switch (get_channel())
		{
			case CH1:
				if ((this->remap == PARTIAL_REMAP1) || (this->remap == FULL_REMAP))
				{
					GPIO(GPIOA, PIN15, AF_OUTPUT_PUSH_PULL_2MHZ);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((this->remap)<<8); //Select the remaping configuration
				}
				else
					GPIO(GPIOA, PIN0, AF_OUTPUT_PUSH_PULL_2MHZ);
					
			break;
			case CH2:
				if ((this->remap == PARTIAL_REMAP1) || (this->remap == FULL_REMAP))
				{
					GPIO(GPIOB, PIN3, AF_OUTPUT_PUSH_PULL_2MHZ);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((this->remap)<<8); //Select the remaping configuration
				}
				else
					GPIO(GPIOA, PIN1, AF_OUTPUT_PUSH_PULL_2MHZ);
					
			break;
			case CH3:
				if ((this->remap == PARTIAL_REMAP2) || (this->remap == FULL_REMAP))
				{
					GPIO(GPIOB, PIN10, AF_OUTPUT_PUSH_PULL_2MHZ);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((this->remap)<<8); //Select the remaping configuration
				}
				else
					GPIO(GPIOA, PIN2, AF_OUTPUT_PUSH_PULL_2MHZ);
					
			break;
			case CH4:
				if ((this->remap == PARTIAL_REMAP2) || (this->remap == FULL_REMAP))
				{
					GPIO(GPIOB, PIN11, AF_OUTPUT_PUSH_PULL_2MHZ);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((this->remap)<<8); //Select the remaping configuration
				}
				else
					GPIO(GPIOA, PIN3, AF_OUTPUT_PUSH_PULL_2MHZ);
		
			break;		
		}	
	}

	if (this->TIM == TIM3) 
	{
		switch (get_channel())
		{
			case CH1:
				if (this->remap == PARTIAL_REMAP1)
				{
					GPIO(GPIOB, PIN4, AF_OUTPUT_PUSH_PULL_2MHZ);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((this->remap)<<10); //Select the remaping configuration
				}
				else
					GPIO(GPIOA, PIN6, AF_OUTPUT_PUSH_PULL_2MHZ);
					
			break;
			case CH2:
				if (this->remap == PARTIAL_REMAP1)
				{
					GPIO(GPIOB, PIN15, AF_OUTPUT_PUSH_PULL_2MHZ);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((this->remap)<<10); //Select the remaping configuration
				}
				else
					GPIO(GPIOA, PIN7, AF_OUTPUT_PUSH_PULL_2MHZ);
					
			break;
			case CH3:
				GPIO(GPIOB, PIN0, AF_OUTPUT_PUSH_PULL_2MHZ);
			break;
			case CH4:
				GPIO(GPIOB, PIN1, AF_OUTPUT_PUSH_PULL_2MHZ);
			break;		
		}
	}
	
	//Remap will make no efect at Timer4 too
	if (this->TIM == TIM4) 
	{
		switch (get_channel())
		{
			case CH1:
				GPIO(GPIOB, PIN6, AF_OUTPUT_PUSH_PULL_2MHZ);
			break;
			case CH2:
				GPIO(GPIOB, PIN7, AF_OUTPUT_PUSH_PULL_2MHZ);
			break;
			case CH3:
				GPIO(GPIOB, PIN8, AF_OUTPUT_PUSH_PULL_2MHZ);
			break;
			case CH4:
				GPIO(GPIOB, PIN9, AF_OUTPUT_PUSH_PULL_2MHZ);
			break;		
		}
	}
	

}

//******************************************************************************************************************************

void PWM::PWMInit()
{
//PSC -> Prescaler
//ARR -> "Auto Reload Register" determinates the period
//CCR1 -> "Capture/Compare Register" Determinates the duty cicle
//CCMR1 -> "Capture/Compare Register" Configure the operation mode of the Capture/Compare Register respective to the selected channel
	
	//This line enable/disable the preload register of CCRx
	//TIM->CCMR1 |= (1<<11); 
	
	/* Uncoment this to get 1kHz of frequency and to be able to write in the CCR1 a value between 0-100 to get 0-100% PWM
	TIM->PSC = 720; //Configure the preescalers
	
	TIM->ARR = 100;
	*/
	
	switch (get_channel())
	{
		case CH1:
			TIM_Write = &(TIM->CCR1);
			*TIM_Write = 0;										//Initialize the PWM with 0%
			TIM->CCMR1 |= (1<<6) | (1<<5);		//Configure the output compare mode as PWM with active mode HIGH
			TIM->CCER |= (1<<0);
			TIM->BDTR |= (1<<15);									//Enable the main output
		break;
		case CH2:
			TIM_Write = &(TIM->CCR2);
			*TIM_Write = 0;										//Initialize the PWM with 0%
			TIM->CCMR1 |= (1<<14) | (1<<13);	//Configure the output compare mode as PWM with active mode HIGH
			TIM->CCER |= (1<<4);
		break;
		case CH3:
			TIM_Write = &(TIM->CCR3);
			*TIM_Write = 0;										//Initialize the PWM with 0%
			TIM->CCMR2 |= (1<<6) | (1<<5);		//Configure the output compare mode as PWM with active mode HIGH
			TIM->CCER |= (1<<8);
		break;
		case CH4:
			TIM_Write = &(TIM->CCR4);
			*TIM_Write = 0;										//Initialize the PWM with 0%
			TIM->CCMR2 |= (1<<14) | (1<<13);	//Configure the output compare mode as PWM with active mode HIGH
			TIM->CCER |= (1<<12);
		break;		
	
	}
	
	
	TIM->CCER |= (1<<(4*get_channel()));	//Enable the channel output
	
	this->TIM->EGR |= (1<<0);							//Update generation -> Generate an uptade of all configurations done before
	
	TIM->CR1 |= (1<<0); 									//Enable the counter
	
}

//******************************************************************************************************************************

void PWM::PWMWrite(uint16_t value)
{
	*TIM_Write = value;
}

