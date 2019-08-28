#ifndef USART_DRIVER
#define USART_DRIVER

#include "Micro.h"
#include "GPIO.h"

//USART 1 - fclk = 72M
//USART 2 e 3 - fclk = 36M
typedef enum{
	BD_9600,
	BD_38400,
	BD_57600,
	BD_115200,	//BD_115384 -> this is the value if using USART 2 or 3
	BD_230769,
	BD_250000,
	BD_1382400,
	BD_1000000,
	BD_2250000,
} BD_ENUM;

class USART
{
	private:
		GPIO TX_Port;
		GPIO RX_Port;
		USART_TypeDef *Usart;
		void init(BD_ENUM Baud_Rate);
	
	public:
		USART(USART_TypeDef *Usart, BD_ENUM Baud_Rate);
		void Send(char value);
		void Send_Vec_16(uint16_t *ptVec, uint16_t size);
		void sendFloat(float *ptFloat);
		void sendUint32(uint32_t *ptUint32);
		void sendUint16(uint16_t *ptUint16);
		uint8_t Receive();
		bool Available();
		
};




#endif
