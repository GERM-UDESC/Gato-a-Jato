#include "Micro.h"
#include "GPIO.h"

const GPIO_STRUCT GPIO_PORTS_PINS[NUM_OF_IOs] =
{
  {GPIOA, PIN0},    
	{GPIOA, PIN1},
	{GPIOA, PIN2},
	{GPIOA, PIN3},
	{GPIOA, PIN4},
	{GPIOA, PIN5},
	{GPIOA, PIN6},
	{GPIOA, PIN7},
	{GPIOA, PIN8},
	{GPIOA, PIN9},
	{GPIOA, PIN10},
	{GPIOA, PIN11},
	{GPIOA, PIN12},
	{GPIOA, PIN15},
	{GPIOB, PIN0}, 
	{GPIOB, PIN1}, 
	{GPIOB, PIN3}, 
	{GPIOB, PIN4}, 
	{GPIOB, PIN5}, 
	{GPIOB, PIN6}, 
	{GPIOB, PIN7}, 
	{GPIOB, PIN8}, 
	{GPIOB, PIN9}, 
	{GPIOB, PIN10}, 
	{GPIOB, PIN11}, 
	{GPIOB, PIN12}, 
	{GPIOB, PIN13}, 
	{GPIOB, PIN14}, 
	{GPIOB, PIN15},
	{GPIOC, PIN13},		//Board Led	- Carefull
	{GPIOC, PIN14}, 	//Carefull
	{GPIOC, PIN15}, 	//Carefull
 };

//Construtores
GPIO::GPIO(GPIO_IO_ENUM IO_Pin, GPIO_MODES GPIOMode)
{
	this->GPIONum = IO_Pin;
	SetGPIOPortPin(IO_Pin);
	SetGPIOMode(GPIOMode);
	ConfigGPIOPin();
	Config_PU_PD(PULL_DOWN);		//Config PULL_DOWN as default
}

//------------------------Config_pin-----------------------------------------------
void GPIO::ConfigGPIOPin()
{
	//UsedPins[this->GPIONum] = HIGH;
	/***************************************************************/
	/*The microcontroller by default reserve 5 pins (PA13,PA14,PA15,PB3 and PB4) for JTAG + SW
		I'm using only St-link (wich uses only SW pins(PA13 and PA14)) and I want to use PA15, PB3 and PB4 in my project,
		I'll by default remap the SWJ _CFG to free the others pins		
		This can be done enabling the clock of AFIO periferal and configuring SWJ _CFG bits to 010, wich means that
		JTAG-DP pins are Disabled and SW-DP pins still Enabled
	*/
	RCC->APB2ENR |= (1<<0);  	//Enable the clock
	AFIO->MAPR |= (1<<25);		//put the "010" into SWJ _CFG bits
	
	/***************************************************************/

	//Enable the clock of the chosen port
	if (GetGPIOPort() == GPIOA)				RCC->APB2ENR |= (1<<2);									
	else if (GetGPIOPort() == GPIOB)		RCC->APB2ENR |= (1<<3);									
	else if (GetGPIOPort() == GPIOC)		RCC->APB2ENR |= (1<<4);
	else if (GetGPIOPort() == GPIOD)		RCC->APB2ENR |= (1<<5);
	else if (GetGPIOPort() == GPIOE)		RCC->APB2ENR |= (1<<6);
	else if (GetGPIOPort() == GPIOF)		RCC->APB2ENR |= (1<<7);
	else if (GetGPIOPort() == GPIOG)		RCC->APB2ENR |= (1<<8);	
	
	//Configure the pin
	if ((GetGPIOPinNumber()) >= PIN8)							//if pin number >= 8, we must use CRH
	{
		//Just converting the pin number to it respective address in the CRH
		uint16_t pin_base = ((GetGPIOPinNumber()) - 8)*4;					
		
		//put all bits related to the pin to 0
		GetGPIOPort()->CRH &= ~((0xF)<<(pin_base));				
		GetGPIOPort()->ODR &= ~(1<<(GetGPIOPinNumber()));		//this line serves to put the output to 0 or to configure the input as pull down as default
		
		//configure the pin
		GetGPIOPort()->CRH |= ((GetGPIOMode())<<(pin_base));
	}
	else
	{
		//Just converting the pin number to it respective address in the CRL
		uint16_t pin_base = GetGPIOPinNumber()*4;					
		
		//put all bits related to the pin to 0
		GetGPIOPort()->CRL &= ~((0xF)<<(pin_base));				
		GetGPIOPort()->ODR &= ~(1<<(GetGPIOPinNumber()));		//this line serves to put the output to 0 or to configure the input as pull down as default
		
		//configure the pin
		GetGPIOPort()->CRL |= ((GetGPIOMode())<<(pin_base));
	}
		
}


//------------------------PU_PD--------------------------------------------------
void GPIO::Config_PU_PD(PU_PD_ENUM PU_PD)
{
	this->PU_PD = PU_PD;
	
	if ((this->PU_PD) == PULL_UP)
		GetGPIOPort()->ODR |= (1<<(GetGPIOPinNumber()));
	else
		GetGPIOPort()->ODR &= ~(1<<(GetGPIOPinNumber()));
}

//------------------------digitalWrite-----------------------------------------------
void GPIO::digitalWrite(bool state)
{
	this->GPIOState = state;
	if (GetGPIOState() == LOW)
		GetGPIOPort()->BSRR |= (1<<(GetGPIOPinNumber()+16));							
	else
		GetGPIOPort()->BSRR |= (1<<(GetGPIOPinNumber()));								//If the state is not LOW, I'll consider it as HIGH
}

//------------------------tooglePin-----------------------------------------------
void GPIO::tooglePin()
{
	GetGPIOPort()->ODR ^=(1<<(GetGPIOPinNumber()));																						//^ means exclusive or
}

//------------------------digitalRead-------------------------------------------------
bool GPIO::digitalRead()
{
	return (GetGPIOPort()->IDR) & (1<<(GetGPIOPinNumber()));
}

//-------------------------------SETTERS------------------------------------
void GPIO::SetGPIOPortPin(GPIO_IO_ENUM IO_Pin)
{
	this->GPIOPortPin.Port = GPIO_PORTS_PINS[IO_Pin].Port;
	this->GPIOPortPin.pinNumber = GPIO_PORTS_PINS[IO_Pin].pinNumber;	
}
void GPIO::SetGPIOMode(GPIO_MODES GPIOMode)
{
	this->GPIOMode = GPIOMode;
}

//-------------------------------GETTERS------------------------------------
GPIO_TypeDef *GPIO::GetGPIOPort()
{
	return this->GPIOPortPin.Port;
}
PIN_NUMBERS GPIO::GetGPIOPinNumber()
{
	return this->GPIOPortPin.pinNumber;
}
GPIO_MODES GPIO::GetGPIOMode()
{
	return this->GPIOMode;
}
PU_PD_ENUM GPIO::GetGPIOPuPd()
{
	return this->PU_PD;
}
bool GPIO::GetGPIOState()
{
	return this->GPIOState;
}
