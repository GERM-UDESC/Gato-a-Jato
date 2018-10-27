#include "PWM.h"

//******************************************************************************************************************************

PWM::PWM(TIM_TypeDef *TIM, TIM_CHANNELS channel, TIM_REMAP PWMremap) : Timer(TIM, channel, PWM_MODE)		//Timer Constructor
{	
	SetPWMRemap(PWMremap);
	
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
			case CH1:
				//GPIO(GPIOA, PIN8, AF_OUTPUT_PUSH_PULL_2MHZ);
				SetGPIOPort(GPIOA);
				SetGPIOPinNumber(PIN8);
				SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
			break;
			case CH2:
				//GPIO(GPIOA, PIN9, AF_OUTPUT_PUSH_PULL_2MHZ);
				SetGPIOPort(GPIOA);
				SetGPIOPinNumber(PIN9);
				SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
			break;
			case CH3:
				//GPIO(GPIOA, PIN10, AF_OUTPUT_PUSH_PULL_2MHZ);
				SetGPIOPort(GPIOA);
				SetGPIOPinNumber(PIN10);
				SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
			break;
			case CH4:
				//GPIO(GPIOA, PIN11, AF_OUTPUT_PUSH_PULL_2MHZ);
				SetGPIOPort(GPIOA);
				SetGPIOPinNumber(PIN11);
				SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
			break;		
		}
	}
	
	if (GetTim() == TIM2) 
	{		
		switch (GetTIMChannel())
		{
			case CH1:
				if ((GetPWMRemap() == PARTIAL_REMAP1) || (GetPWMRemap() == FULL_REMAP))
				{
					//GPIO(GPIOA, PIN15, AF_OUTPUT_PUSH_PULL_2MHZ);
					SetGPIOPort(GPIOA);
					SetGPIOPinNumber(PIN15);
					SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((GetPWMRemap())<<8); //Select the remaping configuration
				}
				else
				{
					//GPIO(GPIOA, PIN0, AF_OUTPUT_PUSH_PULL_2MHZ);
					SetGPIOPort(GPIOA);
					SetGPIOPinNumber(PIN0);
					SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
				}
					
			break;
			case CH2:
				if ((GetPWMRemap() == PARTIAL_REMAP1) || (GetPWMRemap() == FULL_REMAP))
				{
					//GPIO(GPIOB, PIN3, AF_OUTPUT_PUSH_PULL_2MHZ);
					SetGPIOPort(GPIOB);
					SetGPIOPinNumber(PIN3);
					SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((GetPWMRemap())<<8); //Select the remaping configuration
				}
				else
				{
					//GPIO(GPIOA, PIN1, AF_OUTPUT_PUSH_PULL_2MHZ);
					SetGPIOPort(GPIOA);
					SetGPIOPinNumber(PIN1);
					SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
				}
			break;
			case CH3:
				if ((GetPWMRemap() == PARTIAL_REMAP2) || (GetPWMRemap() == FULL_REMAP))
				{
					//GPIO(GPIOB, PIN10, AF_OUTPUT_PUSH_PULL_2MHZ);
					SetGPIOPort(GPIOB);
					SetGPIOPinNumber(PIN10);
					SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((GetPWMRemap())<<8); //Select the remaping configuration
				}
				else
				{
					//GPIO(GPIOA, PIN2, AF_OUTPUT_PUSH_PULL_2MHZ);
					SetGPIOPort(GPIOA);
					SetGPIOPinNumber(PIN2);
					SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
				}	
			break;
			case CH4:
				if ((GetPWMRemap() == PARTIAL_REMAP2) || (GetPWMRemap() == FULL_REMAP))
				{
					//GPIO(GPIOB, PIN11, AF_OUTPUT_PUSH_PULL_2MHZ);
					SetGPIOPort(GPIOB);
					SetGPIOPinNumber(PIN11);
					SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((GetPWMRemap())<<8); //Select the remaping configuration
				}
				else
				{
					//GPIO(GPIOA, PIN3, AF_OUTPUT_PUSH_PULL_2MHZ);
					SetGPIOPort(GPIOA);
					SetGPIOPinNumber(PIN3);
					SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
				}
			break;		
		}	
	}

	if (GetTim() == TIM3) 
	{
		switch (GetTIMChannel())
		{
			case CH1:
				if (GetPWMRemap() == PARTIAL_REMAP2)
				{
					//GPIO(GPIOB, PIN4, AF_OUTPUT_PUSH_PULL_2MHZ);
					SetGPIOPort(GPIOB);
					SetGPIOPinNumber(PIN4);
					SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((GetPWMRemap())<<10); //Select the remaping configuration
				}
				else
				{
					//GPIO(GPIOA, PIN6, AF_OUTPUT_PUSH_PULL_2MHZ);
					SetGPIOPort(GPIOA);
					SetGPIOPinNumber(PIN6);
					SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
				}
					
			break;
			case CH2:
				if (GetPWMRemap() == PARTIAL_REMAP2)
				{
					//GPIO(GPIOB, PIN5, AF_OUTPUT_PUSH_PULL_2MHZ);
					SetGPIOPort(GPIOB);
					SetGPIOPinNumber(PIN5);
					SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
					RCC->APB2ENR |= (1<<0);
					AFIO->MAPR |= ((GetPWMRemap())<<10); //Select the remaping configuration
				}
				else
				{
					//GPIO(GPIOA, PIN7, AF_OUTPUT_PUSH_PULL_2MHZ);
					SetGPIOPort(GPIOA);
					SetGPIOPinNumber(PIN7);
					SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
				}
			break;
			case CH3:
				//GPIO(GPIOB, PIN0, AF_OUTPUT_PUSH_PULL_2MHZ);
				SetGPIOPort(GPIOB);
				SetGPIOPinNumber(PIN0);
				SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
			break;
			case CH4:
				//GPIO(GPIOB, PIN1, AF_OUTPUT_PUSH_PULL_2MHZ);
				SetGPIOPort(GPIOB);
				SetGPIOPinNumber(PIN1);
				SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
			break;		
		}
	}
	
	//Remap will make no efect at Timer4 too
	if (GetTim() == TIM4) 
	{
		switch (GetTIMChannel())
		{
			case CH1:
				//GPIO(GPIOB, PIN6, AF_OUTPUT_PUSH_PULL_2MHZ);
				SetGPIOPort(GPIOB);
				SetGPIOPinNumber(PIN6);
				SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
			break;
			case CH2:
				//GPIO(GPIOB, PIN7, AF_OUTPUT_PUSH_PULL_2MHZ);
				SetGPIOPort(GPIOB);
				SetGPIOPinNumber(PIN7);
				SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
			break;
			case CH3:
				//GPIO(GPIOB, PIN8, AF_OUTPUT_PUSH_PULL_2MHZ);
				SetGPIOPort(GPIOB);
				SetGPIOPinNumber(PIN8);
				SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
			break;
			case CH4:
				//GPIO(GPIOB, PIN9, AF_OUTPUT_PUSH_PULL_2MHZ);
				SetGPIOPort(GPIOB);
				SetGPIOPinNumber(PIN9);
				SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
			break;		
		}
	}
	ConfigGPIOPin();			//After selecting port, pin and GPIOMode, configure the gpio
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
	TIM->PSC = 7200; //Configure the preescalers
	
	//TIM->ARR = 100;
	//*/
	
	switch (GetTIMChannel())
	{
		case CH1:
			PWM_WriteAddress  = &(TIM->CCR1);
			*PWM_WriteAddress  = 0;										//Initialize the PWM with 0%
			TIM->CCMR1 |= (1<<6) | (1<<5);		//Configure the output compare mode as PWM with active mode HIGH
			TIM->BDTR |= (1<<15);							//Enable the main output
		break;
		case CH2:
			PWM_WriteAddress  = &(TIM->CCR2);
			*PWM_WriteAddress  = 0;										//Initialize the PWM with 0%
			TIM->CCMR1 |= (1<<14) | (1<<13);	//Configure the output compare mode as PWM with active mode HIGH
		break;
		case CH3:
			PWM_WriteAddress  = &(TIM->CCR3);
			*PWM_WriteAddress  = 0;										//Initialize the PWM with 0%
			TIM->CCMR2 |= (1<<6) | (1<<5);		//Configure the output compare mode as PWM with active mode HIGH
		break;
		case CH4:
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
