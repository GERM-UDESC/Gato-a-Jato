//#include "stm32f10x.h" // comentar para tirar os arquivos que eu não fiz do programa
#include "micro.h"

int main()
{
	RCC->APB2ENR |= (1<<4);
	
	GPIOC->CRH |= ((1<<20) | (1<<21));
	GPIOC->CRH &= ~((1<<22) | (1<<23));
	
	
	while (1)
	{
	for(int i = 0; i<10; i++);
	GPIOC->BSRR = (1<<13);
	
	for(int i = 0; i<50; i++);
	GPIOC->BSRR = 1<<(13+16);
}

}
