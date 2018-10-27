//#include "stm32f10x.h" // comentar para tirar os arquivos que eu não fiz do programa

#include "Micro.h"
#include "GPIO.h"
#include "TIMER.h"
#include "PWM.h"
#include "SysClock.h"

uint16_t adc_convertion;


//Como fazer uma função que configure só uma vez um remap para todos os canais do timer?

int main()
{
	SysClock Board;
	Board.SysClockInit();
	Board.SysTickInit(BASE_100ms);

	GPIO LED_placa(GPIOC, PIN13, GP_OUTPUT_PUSH_PULL_2MHZ);
	
	//how to use adc:
	//1. calibration
	//2. select a source for adc
	//3. adc enable
	//4. start convertion
	GPIO ADC_test(GPIOA, PIN0, INPUT_ANALOG);
	RCC->APB2ENR |= (1<<9) | (1<<10); //Enable the clock of adc1 and adc2 peripherals
	ADC1->CR2 |= (1<<0);							//Enable the ADON bit, the first time is just to enable, the next one is to start converting
	for(uint8_t i = 0; i < 50; i++);	//It's needed to wait at least 2 ADC cycles before starting the calibration
	ADC1->CR2 |= (1<<2);							//Start the calibration
	while (ADC1->CR2 & (1<<2));				//Wait until the calibration stops
	
	//ADC1->CR1 |= (1<<8);							//enable the scan mode (multichannel mode)
	ADC1->CR2 |= (1<<22);							//Start conversion of regular channels 
	ADC1->CR2 |= (1<<1);							//continuous conversion mode
	
	ADC1->CR2 |= (1<<0);							//now start converting
	
	while(1)
	{
		//while(ADC1->SR & (1<<1));
		//ADC1->SR &= ~(1<<1);						//Clear the EOC (End Of Conversion) flag
		adc_convertion = ADC1->DR;			//save the value of the convertion
		if (Board.SysTickGetEvent()) LED_placa.Toogle_pin();
	}
}

