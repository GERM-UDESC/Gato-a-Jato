//#include "stm32f10x.h" // comentar para tirar os arquivos que eu não fiz do programa

#include "Micro.h"
#include "GPIO.h"
#include "TIMER.h"
#include "PWM.h"
#include "SysClock.h"


int main()
{
	SysClock Board;
	Board.SysClockInit();
	Board.SysTickInit(BASE_100ms);
	//Board.MCO();					//activate the Microcontroller clock output as Sysclock/2
	//Como fazer um getter para uma função que retorna um ponteiro?

	
	GPIO LED_placa(GPIOC, PIN13, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO LED_placa1(GPIOC, PIN1, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO LED_placa0(GPIOC, PIN0, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO LED_placa2(GPIOC, PIN2, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO LED_placa3(GPIOC, PIN3, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO LED_placa4(GPIOC, PIN4, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO LED_placa5(GPIOC, PIN5, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO LED_placa6(GPIOC, PIN6, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO LED_placa7(GPIOC, PIN7, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO LED_placa8(GPIOC, PIN8, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO LED_placa9(GPIOC, PIN9, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO LED_placa10(GPIOC, PIN10, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO LED_placa11(GPIOC, PIN11, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO LED_placa12(GPIOC, PIN12, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO LED_placa14(GPIOC, PIN14, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO LED_placa15(GPIOC, PIN15, GP_OUTPUT_PUSH_PULL_2MHZ);
	
	
//	PWM testePWM(TIM3,CH1,NO_REMAP);	
//	PWM testePWM1(TIM3,CH2,NO_REMAP);
//	PWM testePWM2(TIM3,CH3,NO_REMAP);
//	PWM testePWM3(TIM3,CH4,NO_REMAP);
//	//testePWM.PWMInit();
//	testePWM.PWMWrite(30000);
//	testePWM1.PWMWrite(30000);
//	testePWM2.PWMWrite(30000);
//	testePWM3.PWMWrite(30000);
	RCC->APB1ENR |= (1<<1);
	
	TIM3->CCR1 = 0;
	TIM3->CCMR1 |= (1<<3) | (1<<6) | (1<<5);	//Configure the output compare mode as PWM:1 with active mode HIGH

	TIM3->CCER |= (1<<0);	//Enable the channel output
	
	//TIM3->BDTR |= (1<<15);									//Enable the main output
	TIM3->PSC = 6500; //Configure the preescalers
	
	//TIM3->EGR |= (1<<0);							//Update generation -> Generate an uptade of all configurations done before
	
	TIM3->CCER |= (1<<0);	//Enable the channel output
	
	TIM3->CR1 |= (1<<7);
		
	TIM3->EGR |= (1<<0);							//Update generation -> Generate an uptade of all configurations done before
	
	TIM3->CR1 |= (1<<0); 									//Enable the counter
	
	TIM3->CCR1 = 30000;
	
	GPIO PWMtest(GPIOA, PIN6, AF_OUTPUT_PUSH_PULL_2MHZ);
	
//	RCC->APB2ENR |= (1<<11);
//	GPIO PWMtest1(GPIOA, PIN8, AF_OUTPUT_PUSH_PULL_2MHZ);
//	TIM1->PSC = 65000; //Configure the preescalers
//	TIM1->CCR1 = 0;
//	TIM1->CCMR1 |= (1<<6) | (1<<5);	//Configure the output compare mode as PWM with active mode HIGH

//	TIM1->CCER |= (1<<0);	//Enable the channel output
//	
//	TIM1->BDTR |= (1<<15);									//Enable the main output
//	
//	TIM1->EGR |= (1<<0);							//Update generation -> Generate an uptade of all configurations done before
//	
//	TIM1->CR1 |= (1<<0); 									//Enable the counter
//	
//	TIM1->CCR1 = 30000;
	while(1)
	{
		if (Board.SysTickGetEvent())
		{
			LED_placa.Toogle_pin();
		}
	}
}

