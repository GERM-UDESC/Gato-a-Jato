#include "TIMER.h"
//--------------------------------------------CLASS------------------------------------------------------
//Can't use 
//PWM testePWM(TIM3,CH1,PARTIAL_REMAP2);  //PB4
//PWM testePWM(TIM2,CH1,PARTIAL_REMAP1); //PA15
//PWM testePWM(TIM2,CH2,PARTIAL_REMAP1);	//PB3
class PWM : protected Timer
{
	private:
		//Atributes
		TIM_REMAP PWMremap;
		volatile uint16_t *PWM_WriteAddress;			//Pointer to the CCRx Register

		//Methods
		void ConfigPWMPin();
		void PWMInit();				//This function initialize the PWM with no prescaler and the reset value at ARR
		
		//Setters
		void SetPWMRemap(TIM_REMAP PWMremap);
				
	public:
		//Contructors
		PWM(TIM_TypeDef *TIM, TIM_CHANNELS channel, TIM_REMAP PWMremap);	//This constructor configure the gpio and timer and start the PWM with a 0 duty cicle
		
		//Getters
		TIM_REMAP GetPWMRemap();
		
		//Methods
		void PWMWrite(uint16_t value);	//This function write a PWM value 0-65535
		

	
};
