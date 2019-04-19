#include "USART.h"

USART::USART(USART_TypeDef *Usart, BD_ENUM Baud_Rate)
{
	this->Usart = Usart;
	init(Baud_Rate);	
}

void USART::init(BD_ENUM Baud_Rate)
{

	if (Usart == USART1) 
	{
		RCC->APB2ENR |= (1<<14);	//Enable the clock
		TX_Port.SetGPIOPortPin(PA9);
		RX_Port.SetGPIOPortPin(PA10);
		if (Baud_Rate == BD_9600)	Usart->BRR = 0x1D4C;			
		else if (Baud_Rate == BD_9600)	Usart->BRR = 0xEA2;	
		else if (Baud_Rate == BD_115200)	Usart->BRR = 0x271;
		else if (Baud_Rate == BD_230769)	Usart->BRR = 0x138;
		else if (Baud_Rate == BD_250000)	Usart->BRR = 0x120;
		else if (Baud_Rate == BD_1000000)	Usart->BRR = 0x48;			
		else if (Baud_Rate == BD_2250000)	Usart->BRR = 0x20;		
	}
	else if (Usart == USART2) 
	{
		RCC->APB1ENR |= (1<<17);	//Enable the clock
		TX_Port.SetGPIOPortPin(PA2);
		RX_Port.SetGPIOPortPin(PA3);
		if (Baud_Rate == BD_9600)	Usart->BRR = 0xEA6;			
		else if (Baud_Rate == BD_57600)	Usart->BRR = 0x271;			
		else if (Baud_Rate == BD_115200)	Usart->BRR = 0x138;
		else if (Baud_Rate == BD_230769)	Usart->BRR = 0x9C;
		else if (Baud_Rate == BD_250000)	Usart->BRR = 0x90;
		else if (Baud_Rate == BD_1000000)	Usart->BRR = 0x24;
		else if (Baud_Rate == BD_2250000)	Usart->BRR = 0x10;	
	}
	else if (Usart == USART3) 
	{
		RCC->APB1ENR |= (1<<18);	//Enable the clock
		TX_Port.SetGPIOPortPin(PB10);
		RX_Port.SetGPIOPortPin(PB11);
		if (Baud_Rate == BD_9600)	Usart->BRR = 0xEA6;			
		else if (Baud_Rate == BD_57600)	Usart->BRR = 0x271;			
		else if (Baud_Rate == BD_115200)	Usart->BRR = 0x138;
		else if (Baud_Rate == BD_230769)	Usart->BRR = 0x9C;
		else if (Baud_Rate == BD_250000)	Usart->BRR = 0x90;
		else if (Baud_Rate == BD_1000000)	Usart->BRR = 0x24;
		else if (Baud_Rate == BD_2250000)	Usart->BRR = 0x10;	
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

void USART::Send(char value)
{
	while((Usart->SR & (1<<7)) == 0);      //wait until last data transmission is complete
	Usart->DR = value;                     //transfer data to DR register
}

void USART::Send_Vec_16(uint16_t *ptVec, uint16_t size)
{
	for (uint16_t i = 0; i < size; i++)
	{
		Send((uint8_t)(*ptVec & 0xFF));
		Send(*ptVec >> 8);
		ptVec++;
	}
}

void USART::sendUint16(uint16_t *ptUint16)
{
	unsigned char *chptr;
	chptr = (unsigned char *) ptUint16;
	Send(*chptr++);
	Send(*chptr);
}

void USART::sendFloat(float *ptFloat)
{
	unsigned char *chptr;
	chptr = (unsigned char *) ptFloat;
	Send(*chptr++);
	Send(*chptr++);
	Send(*chptr++);
	Send(*chptr);
}

void USART::sendUint32(uint32_t *ptUint32)
{
	unsigned char *chptr;
	chptr = (unsigned char *) ptUint32;
	Send(*chptr++);
	Send(*chptr++);
	Send(*chptr++);
	Send(*chptr);
}

void sendUint32(uint32_t *ptUint32);

uint8_t USART::Receive()
{
	while((Usart->SR & (1<<5)) == 0)
		;  			//wait until data is available for reading
  return (Usart->DR & 0xFF);              //return read data
}

bool USART::Available()
{
	if (Usart->SR & (1<<5)) return 1;	//if there is something, return 1, else, return 0
	return 0;
}

