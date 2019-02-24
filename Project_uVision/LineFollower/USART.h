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
		
	
	
	
	
};




#endif