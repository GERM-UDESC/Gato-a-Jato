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

	GPIO LED_placa(GPIOC, PIN13, GP_OUTPUT_PUSH_PULL_2MHZ);
	
	PWM testePWM(TIM3,CH1,NO_REMAP);	
	
	while(1)
	{
		if (Board.SysTickGetEvent())
		{
			LED_placa.Toogle_pin();
		}
	}
}

