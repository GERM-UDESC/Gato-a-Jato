#include "PWM.h"

//******************************************************************************************************************************

PWM::PWM(TIM_TypeDef *TIM, TIM_CHANNELS channel, TIM_REMAP PWMremap) : Timer(TIM, channel, PWM_MODE)		//Timer Constructor
{	
	SetPWMRemap(PWMremap);
	
	ConfigPWM();
	PWMInit();
}

//******************************************************************************************************************************

void PWM::ConfigPWM()	
{
	//Remap will make no efect at Timer1
	if (GetTim() == TIM1) 
	{
		switch (GetTIMChannel())
		{
			case TIM_CH1:
				PWMPin.SetGPIOPortPin(PA8);
			break;
			case TIM_CH2:
				PWMPin.SetGPIOPortPin(PA9);
			break;
			case TIM_CH3:
				PWMPin.SetGPIOPortPin(PA10);
			break;
			case TIM_CH4:
				PWMPin.SetGPIOPortPin(PA11);
			break;		
		}
	}
	
	if (GetTim() == TIM2) 
	{		
		switch (GetTIMChannel())
		{
			case TIM_CH1:
				if ((GetPWMRemap() == PARTIAL_REMAP1) || (GetPWMRemap() == FULL_REMAP))
				{
					PWMPin.SetGPIOPortPin(PA15);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((GetPWMRemap())<<8); //Select the remaping configuration
				}
				else PWMPin.SetGPIOPortPin(PA0);
				
					
			break;
			case TIM_CH2:
				if ((GetPWMRemap() == PARTIAL_REMAP1) || (GetPWMRemap() == FULL_REMAP))
				{
					PWMPin.SetGPIOPortPin(PB3);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((GetPWMRemap())<<8); //Select the remaping configuration
				}
				else PWMPin.SetGPIOPortPin(PA1);
				
			break;
			case TIM_CH3:
				if ((GetPWMRemap() == PARTIAL_REMAP2) || (GetPWMRemap() == FULL_REMAP))
				{
					PWMPin.SetGPIOPortPin(PB10);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((GetPWMRemap())<<8); //Select the remaping configuration
				}
				else PWMPin.SetGPIOPortPin(PA2);
				
			break;
			case TIM_CH4:
				if ((GetPWMRemap() == PARTIAL_REMAP2) || (GetPWMRemap() == FULL_REMAP))
				{
					PWMPin.SetGPIOPortPin(PB11);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((GetPWMRemap())<<8); //Select the remaping configuration
				}
				else PWMPin.SetGPIOPortPin(PA3);
			break;		
		}	
	}

	if (GetTim() == TIM3) 
	{
		switch (GetTIMChannel())
		{
			case TIM_CH1:
				if (GetPWMRemap() == PARTIAL_REMAP2)
				{
					PWMPin.SetGPIOPortPin(PB4);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((GetPWMRemap())<<10); //Select the remaping configuration
				}
				else PWMPin.SetGPIOPortPin(PA6);					
			break;
			case TIM_CH2:
				if (GetPWMRemap() == PARTIAL_REMAP2)
				{
					PWMPin.SetGPIOPortPin(PB5);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((GetPWMRemap())<<10); //Select the remaping configuration
				}
				else PWMPin.SetGPIOPortPin(PA7);
			break;
			case TIM_CH3:
				PWMPin.SetGPIOPortPin(PB0);
			break;
			case TIM_CH4:
				PWMPin.SetGPIOPortPin(PB1);
			break;		
		}
	}
	
	//Remap will make no efect at Timer4 too
	if (GetTim() == TIM4) 
	{
		switch (GetTIMChannel())
		{
			case TIM_CH1:
				PWMPin.SetGPIOPortPin(PB6);
			break;
			case TIM_CH2:
				PWMPin.SetGPIOPortPin(PB7);
			break;
			case TIM_CH3:
				PWMPin.SetGPIOPortPin(PB8);
			break;
			case TIM_CH4:
				PWMPin.SetGPIOPortPin(PB9);
			break;		
		}
	}
	
	PWMPin.SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);	//Default to PWM pins
	PWMPin.ConfigGPIOPin();			//After selecting port, pin and GPIOMode, configure the gpio
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
	
	///* Uncoment this to get 1kHz of frequency and to be able to write in the CCR1 a value between 0-100 to get 0-100% PWM
	//TIM->PSC = 7200; //Configure the preescalers
	
	//TIM->ARR = 100;
	//*/
	
	switch (GetTIMChannel())
	{
		case TIM_CH1:
			PWM_WriteAddress  = &(TIM->CCR1);
			*PWM_WriteAddress  = 0;										//Initialize the PWM with 0%
			TIM->CCMR1 |= (1<<6) | (1<<5);		//Configure the output compare mode as PWM with active mode HIGH
			TIM->BDTR |= (1<<15);							//Enable the main output
		break;
		case TIM_CH2:
			PWM_WriteAddress  = &(TIM->CCR2);
			*PWM_WriteAddress  = 0;										//Initialize the PWM with 0%
			TIM->CCMR1 |= (1<<14) | (1<<13);	//Configure the output compare mode as PWM with active mode HIGH
		break;
		case TIM_CH3:
			PWM_WriteAddress  = &(TIM->CCR3);
			*PWM_WriteAddress  = 0;										//Initialize the PWM with 0%
			TIM->CCMR2 |= (1<<6) | (1<<5);		//Configure the output compare mode as PWM with active mode HIGH
		break;
		case TIM_CH4:
			PWM_WriteAddress  = &(TIM->CCR4);
			*PWM_WriteAddress  = 0;										//Initialize the PWM with 0%
			TIM->CCMR2 |= (1<<14) | (1<<13);	//Configure the output compare mode as PWM with active mode HIGH
		break;		
	
	}
	TIM->CCER |= (1<<(4*GetTIMChannel()));	//Enable the channel output
	
	TIM->EGR |= (1<<0);							//Update generation -> Generate an uptade of all configurations done before
	
	TIM->CR1 |= (1<<0); 									//Enable the counter
	
}

//******************************************************************************************************************************

void PWM::PWMWrite(uint16_t value)
{
	*PWM_WriteAddress  = value;
}


//-------------------------------SETTERS------------------------------------
void PWM::SetPWMRemap(TIM_REMAP PWMremap)
{
	this->PWMremap = PWMremap;
}

//-------------------------------GETTERS------------------------------------
TIM_REMAP PWM::GetPWMRemap()
{
	return this->PWMremap;
}
