#ifndef	TIMER_DRIVER
#define TIMER_DRIVER
#include "GPIO.h"
#include "Micro.h"

/*The PWM and encoder mode are used just to make a correct distintion between the modes, but the only one that makes difference
in this driver is the counter, because in the encoder e pwm mode, their own drivers take care about their configuration.
*/
typedef enum{
	COUNTER = 0,
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


#define Prescale 71     //Timer frequency = 72Mhz/(Prescale+1). If Prescale = 71, then Timer freq. = 1Mhz -> Timer period = 1us.
#define Time_between_int 10000		//in usec
#define AutoReload_Counter (Time_between_int-1)	//at 1Mhz, and autoreaload_counter = 999, the timer counter will generate an interrupt at each 1ms.



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

	static uint32_t time_in_usec;
	static TIM_TypeDef *TIM_Timer_Counter;

	TIM_CHANNELS TIMChannel;
	TIM_MODE TIMMode;
	
protected:
	//Atributes
	TIM_TypeDef *TIM;
	
	Timer(){};					//Default Constructor 
	
	//Setters
	void SetTim(TIM_TypeDef *TIM);
	void SetTIMChannel(TIM_CHANNELS TIMChannel);
	void SetTIMMode(TIM_MODE TIMMode);
	
public:
	
	static uint32_t GetTime_usec();
	static void Timer_Initiallize();				//Initiallize all timer's static variables
	static void Timer_Handler();		//Take care of all that is need to maintain the time base in usec

	//Constructor
	Timer(TIM_TypeDef *TIM, TIM_CHANNELS TIMChannel, TIM_MODE TIMMode);	
	Timer(TIM_TypeDef *TIM, TIM_MODE TIMMode);
	
	//Public Setters
	void SetTIMRemap(TIM_REMAP TIMRemap);
	
	//Getters 
	TIM_TypeDef* GetTim();
	TIM_CHANNELS GetTIMChannel();
	TIM_MODE GetTIMMode();
	TIM_REMAP GetTIMRemap();

	
	//Methods
	void TimerInit();
	void InterrupTime(uint16_t time);			//in micro seconds -> 0<time<65000
	void ClearInterruptFlag();
		
};


#endif
