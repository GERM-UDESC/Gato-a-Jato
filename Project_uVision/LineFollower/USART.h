#ifndef USART_DRIVER
#define USART_DRIVER

#include "Micro.h"
#include "GPIO.h"

class USART
{
	private:
		GPIO TX_Port;
		GPIO RX_Port;
		USART_TypeDef *Usart;
		void init();
	
	public:
		USART(USART_TypeDef *Usart);
		void Send(uint8_t value);
		void Send_Vec_16(uint16_t *ptVec, uint16_t size);
		uint8_t Receive();
	
	
	
	
};




#endif
