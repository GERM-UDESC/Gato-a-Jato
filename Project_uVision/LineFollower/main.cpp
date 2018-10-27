//#include "stm32f10x.h" // comentar para tirar os arquivos que eu não fiz do programa

#include "Micro.h"
#include "GPIO.h"
#include "TIMER.h"
#include "PWM.h"
#include "SysClock.h"


//Como fazer uma função que configure só uma vez um remap para todos os canais do timer?

int main()
{
	SysClock Board;
	Board.SysClockInit();
	Board.SysTickInit(BASE_100ms);

	GPIO LED_placa(GPIOC, PIN13, GP_OUTPUT_PUSH_PULL_2MHZ);
	
	//PWM testePWM(TIM3,CH1,PARTIAL_REMAP2);  //This one PB4 HAS A PROBLEM, timer is ok because all other channels are working fine
																					//The compare register is also right configured
	//PWM testePWM(TIM2,CH1,PARTIAL_REMAP1); //PA15
	//PWM testePWM1(TIM2,CH2,PARTIAL_REMAP1);	//PB3
	
	
	PWM testePWM(TIM2,CH1,FULL_REMAP);
	PWM testePWM1(TIM2,CH2,FULL_REMAP);
	PWM testePWM2(TIM2,CH3,FULL_REMAP);
	PWM testePWM3(TIM2,CH4,FULL_REMAP);
	testePWM.PWMWrite(10000);
	testePWM1.PWMWrite(25000);
	testePWM2.PWMWrite(40000);
	testePWM3.PWMWrite(55000);
	
	while(1)
	{
		if (Board.SysTickGetEvent())
		{
			LED_placa.Toogle_pin();
		}
	}
}

