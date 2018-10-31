#include "ADC.h"

ADC::ADC(ADC_CHANNELS ADCChannel)
{
	RCC->APB2ENR |= (1<<9) | (1<<10); //IF not enable, enable the clock of adc1 and adc2 peripherals
	
	SetADCMode(SINGLE_CONVERSION); 		//default
	SetADCChannel(ADCChannel);
		
	if(GetADCChannel() == ADC_CH0)	SetGPIOPortPin(PA0);
	else if (GetADCChannel() == ADC_CH1)	SetGPIOPortPin(PA1);
	else if (GetADCChannel() == ADC_CH2)	SetGPIOPortPin(PA2);
	else if (GetADCChannel() == ADC_CH3)	SetGPIOPortPin(PA3);
	else if (GetADCChannel() == ADC_CH4)	SetGPIOPortPin(PA4);
	else if (GetADCChannel() == ADC_CH5)	SetGPIOPortPin(PA5);
	else if (GetADCChannel() == ADC_CH6)	SetGPIOPortPin(PA6);
	else if (GetADCChannel() == ADC_CH7)	SetGPIOPortPin(PA7);
	else if (GetADCChannel() == ADC_CH8)	SetGPIOPortPin(PB0);
	else if (GetADCChannel() == ADC_CH9)	SetGPIOPortPin(PB1);
	
	SetGPIOMode(INPUT_ANALOG);	//Default for adc channels
	
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
