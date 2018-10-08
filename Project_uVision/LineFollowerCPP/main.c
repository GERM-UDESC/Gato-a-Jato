//#include "stm32f10x.h" // comentar para tirar os arquivos que eu não fiz do programa
#include "GPIO.h"

void delay(int time);

int main()
{

	Config_pin(GPIOC, 13, OUTPUT);
	
	while (1)
	{
	delay(500000);
	Toogle_pin(GPIOC, 13);
	}

	
}

void delay(int time)
{
	int i = 0;
	while( i < time) i++;
}


