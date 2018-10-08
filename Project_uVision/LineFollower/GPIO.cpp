#include "GPIO.h"
#include "stdint.h"

class GPIO
{
	public:
		GPIO_TypeDef *port;					
		uint32_t pinNumber;
		uint32_t mode;
		uint32_t state;							//in case it's output
		




};


