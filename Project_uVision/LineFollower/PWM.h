#include "TIMER.h"
//--------------------------------------------CLASS------------------------------------------------------
class PWM : protected Timer
{
	private:
		//Atributes
		TIM_REMAP remap;
		volatile uint16_t *TIM_Write;			//Pointer to the CCRx Register

		//Methods
		void ConfigPWMPin();
				
	public:
		//Contructors
		PWM(TIM_TypeDef *TIM, TIM_CHANNELS channel, TIM_REMAP remap);	//This constructor configure the gpio and timer and start the PWM with a 0 duty cicle
		
		//Methods
		void PWMWrite(uint16_t value);	//This function write a PWM value 0-65535
		
		void PWMInit();			//This function initialize the PWM with no prescaler and the reset value at ARR
	
};
