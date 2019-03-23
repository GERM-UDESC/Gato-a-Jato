#ifndef	PWM_DRIVER
#define PWM_DRIVER
#include "GPIO.h"
#include "TIMER.h"

#define Timer_Frequency 36000000
#define PWM_Frequency 10000				//min PWM frequecy == 600
#define AutoReloadPWM ((Timer_Frequency/PWM_Frequency) - 1) //this is also the maximum writtable pwm value
#define Max_PWM AutoReloadPWM

//--------------------------------------------CLASS------------------------------------------------------
class PWM : protected Timer
{
	private:
		GPIO PWMPin;
		volatile uint16_t *PWM_WriteAddress;			//Pointer to the CCRx Register

		void ConfigPWMPin();
		void PWMInit();				//This function initialize the PWM with no prescaler and the reset value at ARR
				
	public:
		PWM(){};
		PWM(TIM_TypeDef *TIM, TIM_CHANNELS channel, TIM_REMAP PWMremap);	//This constructor configure the gpio and timer and start the PWM with a 0 duty cicle
		PWM(PWM *pwm);
		void PWMWrite(float value);	//This function write a PWM value 0-100%
		
};

#endif
