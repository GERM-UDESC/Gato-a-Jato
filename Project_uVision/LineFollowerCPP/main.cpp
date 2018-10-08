//#include "stm32f10x.h" // comentar para tirar os arquivos que eu não fiz do programa

#include "Micro.h"
#include "GPIO.h"



int main()
{
	GPIO_class LED13;
	
	

	LED13.Config_pin(GPIOC, 13, OUTPUT);
	
	while (1)
	{

	for (int i = 0; i<500000 ; i++);
	LED13.Toogle_pin(GPIOC, 13);
	}

	
}

