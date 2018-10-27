#include "ADC.h"

ADC::ADC(ADC_CHANNELS ADCChannel)
{
	RCC->APB2ENR |= (1<<9) | (1<<10); //IF not enable, enable the clock of adc1 and adc2 peripherals
	
	SetADCMode(SINGLE_CONVERSION); 		//default
	SetADCChannel(ADCChannel);
		
	
	if(GetADCChannel() <= ADC_CH7) SetGPIOPort(GPIOA);				//CH0-CH7 are conected to gpioa
	else if (GetADCChannel() <= ADC_CH9) SetGPIOPort(GPIOB);	//CH8 and CH9 are PB0 and PB1
	
	
	if(GetADCChannel() == ADC_CH0)	SetGPIOPinNumber(PIN0);
	else if (GetADCChannel() == ADC_CH1)	SetGPIOPinNumber(PIN1);
	else if (GetADCChannel() == ADC_CH2)	SetGPIOPinNumber(PIN2);
	else if (GetADCChannel() == ADC_CH3)	SetGPIOPinNumber(PIN3);
	else if (GetADCChannel() == ADC_CH4)	SetGPIOPinNumber(PIN4);
	else if (GetADCChannel() == ADC_CH5)	SetGPIOPinNumber(PIN5);
	else if (GetADCChannel() == ADC_CH6)	SetGPIOPinNumber(PIN6);
	else if (GetADCChannel() == ADC_CH7)	SetGPIOPinNumber(PIN7);
	else if (GetADCChannel() == ADC_CH8)	SetGPIOPinNumber(PIN0);
	else if (GetADCChannel() == ADC_CH9)	SetGPIOPinNumber(PIN1);
	
	SetGPIOMode(INPUT_ANALOG);	//This is needed in order to use the pin as one adc channel
	
	ConfigGPIOPin();
	ADC1->CR2 |= (1<<19) | (1<<18) | (1<<17);
	ADCCalibrate();

}

void ADC::ADCCalibrate()
{
	ADC1->CR2 |= (1<<0);							//Enable the ADON bit, the first time is just to enable, the next one is to start converting
	for(uint8_t i = 0; i < 50; i++);	//It's needed to wait at least 2 ADC cycles before starting the calibration
	ADC1->CR2 |= (1<<2);							//Start the calibration
	while (ADC1->CR2 & (1<<2));				//Wait until the calibration stops
}

//Methods
uint16_t ADC::analogRead()
{
	ADC1->SQR3 &= ~(0xF<<0);					//clear the bits
	ADC1->SQR3 |= (GetADCChannel()<<0);		//select the channel to start converting
	ADC1->CR2 |= (1<<0);							//Start converting
	while(!(ADC1->SR & (1<<1)));			//Wait until the convertion is finished
	ADC1->SR &= ~(1<<1);
	return (ADC1->DR);								//return the convertion value
}

//Setters
void ADC::SetADCMode(ADC_CONVERSION_MODES ADCMode)
{
	this->ADCMode = ADCMode;
}
void ADC::SetADCChannel(ADC_CHANNELS ADCChannel)
{
	this->ADCChannel = ADCChannel;
}

//Getters
ADC_CONVERSION_MODES ADC::GetADCMode()
{
	return (this->ADCMode);
}
ADC_CHANNELS ADC::GetADCChannel()
{
	return (this->ADCChannel);
}
