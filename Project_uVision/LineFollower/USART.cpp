#include "USART.h"

USART::USART(USART_TypeDef *Usart)
{
	this->Usart = Usart;
	init();	
}

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

void USART::Send(uint8_t value)
{
	while((Usart->SR & (1<<7)) == 0);      //wait until data transmission is complete
	Usart->DR = value;                     //transfer data to DR register
}

void USART::Send_Vec_16(uint16_t *ptVec, uint16_t size)
{
	for (uint16_t i = 0; i < size; i++)
	{
		Send(*ptVec >> 8);
		Send((uint8_t)(*ptVec & 0xFF));
		ptVec++;
	}
	
}



uint8_t USART::Receive()
{
	while((Usart->SR & (1<<5)) == 0);  			//wait until data is available for reading
  return (Usart->DR & 0xFF);              //return read data
}



