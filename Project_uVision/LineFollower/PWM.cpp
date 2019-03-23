#include "PWM.h"

//******************************************************************************************************************************

PWM::PWM(TIM_TypeDef *TIM, TIM_CHANNELS channel, TIM_REMAP TIMremap) 
: Timer(TIM, channel, PWM_MODE)		//Timer Constructor
{	
	SetTIMRemap(TIMremap);
	
	ConfigPWMPin();
	PWMInit();
}

PWM::PWM(PWM *pwm) : Timer(pwm->GetTim(), pwm->GetTIMChannel(), PWM_MODE)
{
	SetTIMRemap(pwm->GetTIMRemap());
	
	ConfigPWMPin();
	PWMInit();
	
}

//******************************************************************************************************************************

void PWM::ConfigPWMPin()	
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
				if ((GetTIMRemap() == PARTIAL_REMAP1) || (GetTIMRemap() == FULL_REMAP))
				{
					PWMPin.SetGPIOPortPin(PA15);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((GetTIMRemap())<<8); //Select the remaping configuration
				}
				else PWMPin.SetGPIOPortPin(PA0);
				
			break;
			case TIM_CH2:
				if ((GetTIMRemap() == PARTIAL_REMAP1) || (GetTIMRemap() == FULL_REMAP))
				{
					PWMPin.SetGPIOPortPin(PB3);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((GetTIMRemap())<<8); //Select the remaping configuration
				}
				else PWMPin.SetGPIOPortPin(PA1);
				
			break;
			case TIM_CH3:
				if ((GetTIMRemap() == PARTIAL_REMAP2) || (GetTIMRemap() == FULL_REMAP))
				{
					PWMPin.SetGPIOPortPin(PB10);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((GetTIMRemap())<<8); //Select the remaping configuration
				}
				else PWMPin.SetGPIOPortPin(PA2);
				
			break;
			case TIM_CH4:
				if ((GetTIMRemap() == PARTIAL_REMAP2) || (GetTIMRemap() == FULL_REMAP))
				{
					PWMPin.SetGPIOPortPin(PB11);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((GetTIMRemap())<<8); //Select the remaping configuration
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
				if (GetTIMRemap() == PARTIAL_REMAP2)
				{
					PWMPin.SetGPIOPortPin(PB4);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((GetTIMRemap())<<10); //Select the remaping configuration
				}
				else PWMPin.SetGPIOPortPin(PA6);					
			break;
			case TIM_CH2:
				if (GetTIMRemap() == PARTIAL_REMAP2)
				{
					PWMPin.SetGPIOPortPin(PB5);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((GetTIMRemap())<<10); //Select the remaping configuration
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
//CCMR1 -> "Capture/Compare Mode Register" Configure the operation mode of the Capture/Compare Register respective to the selected channel

	if (GetTim() == TIM1)				//just need a different one for timer1, because it is and advanced timer
	{
		GetTim()->BDTR |= (1<<15);							//Enable the main output
		GetTim()->PSC = 1;											//to get 36MHz of frequency, the same as the others timers
	}
	
	switch (GetTIMChannel())
	{
		case TIM_CH1:
			PWM_WriteAddress  = &(TIM->CCR1);
			*PWM_WriteAddress  = 0;									//Initialize the PWM with 0%
			GetTim()->CCMR1 |= (1<<6) | (1<<5);			//Configure the output compare mode as PWM with active mode HIGH
		break;
		case TIM_CH2:
			PWM_WriteAddress  = &(TIM->CCR2);
			*PWM_WriteAddress  = 0;									//Initialize the PWM with 0%
			GetTim()->CCMR1 |= (1<<14) | (1<<13);		//Configure the output compare mode as PWM with active mode HIGH
		break;
		case TIM_CH3:
			PWM_WriteAddress  = &(TIM->CCR3);
			*PWM_WriteAddress  = 0;									//Initialize the PWM with 0%
			GetTim()->CCMR2 |= (1<<6) | (1<<5);			//Configure the output compare mode as PWM with active mode HIGH
		break;
		case TIM_CH4:
			PWM_WriteAddress  = &(TIM->CCR4);
			*PWM_WriteAddress  = 0;									//Initialize the PWM with 0%
			GetTim()->CCMR2 |= (1<<14) | (1<<13);		//Configure the output compare mode as PWM with active mode HIGH
		break;		
	}	
	
	GetTim()->ARR = AutoReloadPWM;
	
	GetTim()->CCER |= (1<<(4*GetTIMChannel()));	//Enable the channel output
	
	GetTim()->EGR |= (1<<0);										//Update generation -> Generate an uptade of all configurations done before
	
	GetTim()->CR1 |= (1<<0); 										//Enable the counter
	
}

//******************************************************************************************************************************

void PWM::PWMWrite(float value)
{
	if ((value <= 100) && (value >= 0)) 
		*PWM_WriteAddress  = (uint16_t)((value*Max_PWM)/100);
	else if (value >= 100) 	*PWM_WriteAddress  = (uint16_t)Max_PWM;
	else if (value <= 0)		*PWM_WriteAddress  = 0;
}
