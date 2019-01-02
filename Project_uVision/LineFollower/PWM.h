#ifndef	PWM_DRIVER
#define PWM_DRIVER
#include "GPIO.h"
#include "TIMER.h"
//--------------------------------------------CLASS------------------------------------------------------
class PWM : protected Timer
{
	friend class Motor;
	private:
		GPIO PWMPin;
		volatile uint16_t *PWM_WriteAddress;			//Pointer to the CCRx Register

		void ConfigPWMPin();
		void PWMInit();				//This function initialize the PWM with no prescaler and the reset value at ARR
				
	public:
		PWM(){};
		PWM(TIM_TypeDef *TIM, TIM_CHANNELS channel, TIM_REMAP PWMremap);	//This constructor configure the gpio and timer and start the PWM with a 0 duty cicle
		void PWMWrite(uint16_t value);	//This function write a PWM value 0-65535
		
};

#endif
