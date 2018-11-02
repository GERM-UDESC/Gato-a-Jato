#include "GPIO.h"
#include "Micro.h"

#pragma once

typedef enum{
	INPUT_CAPTURE_MODE = 0,
	OUTPUT_COMPARE_MODE,
	COUNTER,
	PWM_MODE,
	QUADRATURE_ENCODER_MODE,
}TIM_MODE;

typedef enum{
	TIM_CH1 = 0,
	TIM_CH2,
	TIM_CH3,
	TIM_CH4,
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
class Timer
{
	private:
		//Atributes
		static TIM_REMAP TIM1Remap;
		static TIM_REMAP TIM2Remap;
		static TIM_REMAP TIM3Remap;
		static TIM_REMAP TIM4Remap;
		
		TIM_REMAP TIMRemap;
		TIM_CHANNELS TIMChannel;
		TIM_MODE TIMMode;
		
	protected:
		//Atributes
		TIM_TypeDef *TIM;		//can/should I do a getter?
		
		Timer(){};					//Default Constructor 
		
		//Setters
		void SetTim(TIM_TypeDef *TIM);
		void SetTIMChannel(TIM_CHANNELS TIMChannel);
		void SetTIMMode(TIM_MODE TIMMode);
		
	public:
		//Constructor
		Timer(TIM_TypeDef *TIM, TIM_CHANNELS TIMChannel, TIM_MODE TIMMode);	
		Timer(TIM_TypeDef *TIM, TIM_MODE TIMMode);
		
		//Public Setters
		void SetTIMRemap(TIM_REMAP TIMRemap);
		
		//Getters 
		TIM_TypeDef* GetTim();
		TIM_CHANNELS GetTIMChannel();
		TIM_MODE GetTIMMode();
		
		//Methods
		void TimerInit();
		void InterrupTime(uint16_t time);			//in micro seconds -> 0<time<65000
		void ClearInterruptFlag();
		
};
