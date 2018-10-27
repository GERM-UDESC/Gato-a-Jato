#include "GPIO.h"

#pragma once

typedef enum{
	INPUT_CAPTURE_MODE = 0,
	OUTPUT_COMPARE_MODE,
	PWM_MODE,
	QUADRATURE_ENCODER_MODE,
}TIM_MODE_IO;

typedef enum{
	CH1 = 0,
	CH2,
	CH3,
	CH4,
}TIM_CHANNELS;

/*
	Timer1 -> No remap  ; //Timer1 can remap some complementary channels, but I'll avoid to use it
	Timer2 -> All options
	Timer3 -> No remap; Partial_Remap2
	Timer4 -> No remap
*/
typedef enum{		
	NO_REMAP = 0,
	PARTIAL_REMAP1,
	PARTIAL_REMAP2,
	FULL_REMAP,
}TIM_REMAP;




//--------------------------------------------CLASS------------------------------------------------------

//TIM2, TIM3, TIM4 -> GenTimer
//TIM1 -> AdvancedTimer
class Timer : protected GPIO
{
	private:
		//Atributes
		TIM_CHANNELS channel;
		TIM_MODE_IO mode;
		
	protected:
		//Atributes
		TIM_TypeDef *TIM;		//can/should I do a getter?
		
		Timer(){};					//Default Constructor 
		
		//Setters
		void SetTimer(TIM_TypeDef *TIM);
		void SetChannel(TIM_CHANNELS channel);
		void SetMode(TIM_MODE_IO mode);
		
	public:
		//Constructor
		Timer(TIM_TypeDef *TIM, TIM_CHANNELS channel, TIM_MODE_IO mode);		
		
		//Getters 
		TIM_TypeDef* GetTimer();
		TIM_CHANNELS get_channel();
		TIM_MODE_IO get_mode();
		
		//Methods
		void TimerInit();
};
