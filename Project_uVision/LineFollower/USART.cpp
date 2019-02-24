#include "USART.h"

void USART::init()
{

	if (Usart == USART1) 
	{
		RCC->APB2ENR |= (1<<14);	//Enable the clock
		TX_Port.SetGPIOPortPin(PA9);
		RX_Port.SetGPIOPortPin(PA10);
		Usart->BRR = 0x1D4C;			//BR 9600
	}
	else if (Usart == USART2) 
	{
		RCC->APB1ENR |= (1<<17);	//Enable the clock
		TX_Port.SetGPIOPortPin(PA2);
		RX_Port.SetGPIOPortPin(PA3);
		Usart->BRR = 0xEA6;					//BR 9600
	}
	else if (Usart == USART3) 
	{
		RCC->APB1ENR |= (1<<18);	//Enable the clock
		TX_Port.SetGPIOPortPin(PB10);
		RX_Port.SetGPIOPortPin(PB11);
		Usart->BRR = 0xEA6;				//BR 9600
	}	
	TX_Port.SetGPIOMode(AF_OUTPUT_PUSH_PULL_2MHZ);
	RX_Port.SetGPIOMode(INPUT_FLOATING);
	TX_Port.ConfigGPIOPin();
	RX_Port.ConfigGPIOPin();
	
	
//	Usart->CR1 |= (1<<5);   //Enable RXNE interrupt
//	Usart->CR1 |= (1<<7);   //Enable TXE interrupt
	Usart->CR1 |= (1<<3);   //Enable transmiter
	Usart->CR1 |= (1<<2);   //Enable receiver
	Usart->CR1 |= (1<<13);	//Enable USART peripheral
	
	
}



