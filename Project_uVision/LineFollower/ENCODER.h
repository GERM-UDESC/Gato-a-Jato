#ifndef ENCODER_DRIVER
#define ENCODER_DRIVER
#include "GPIO.h"
#include "TIMER.h"

#define NUMBER_OF_ENCODERS 4		//the number of timers in the microcontroller, but TIM2 is used for time base
#define min_rpm_precision 5
#define Max_speed_variation 300
#define Max_delay_Ticks_Time (500000/min_rpm_precision)	//This value is used to make shure that the motor speed i'll go to zero
#define AutoReaload_Ticks 11// for pololu encoders, if you want speed, this cannot be lower then 11
#define Ticks_till_int (AutoReaload_Ticks+1)  //Ticks to generate an interruption

/*
	If you want to change the timer used for time base and use it as encoder, just uncomment the lines of the actuall time base timer
	and comment the line of the new time base timer (the interrupt handling lines)
*/

//Encoder 1 - Interrupt Handler
extern "C" void TIM1_UP_IRQHandler();
////Encoder 2 - Interrupt Handler		//this timer is being used as time base for the system
//extern "C" void TIM2_IRQHandler();
//Encoder 3 - Interrupt Handler
extern "C" void TIM3_IRQHandler();
//Encoder 4 - Interrupt Handler
extern "C" void TIM4_IRQHandler();

typedef enum{
	Encoder_TIM1 = 0,
	Encoder_TIM2,
	Encoder_TIM3,
	Encoder_TIM4,
}ENCODER_ENUM;

class Encoder : protected Timer
{
	friend class Motor;
	private:			//should be private
		
		static uint32_t Ticks[NUMBER_OF_ENCODERS];
		static uint32_t Ticks_Time[NUMBER_OF_ENCODERS];
		static uint32_t LastTicks_Time[NUMBER_OF_ENCODERS];
	
		GPIO EncCH1;
		GPIO EncCH2;

		void ConfigEncoder();

	public:
		Encoder(){};					//must be used only by class composition
		Encoder(TIM_TypeDef *TIM);
		uint16_t GetEncTicks();
		float GetEncSpeed();
			
		static void Encoder_Initiallize();
		static void Encoder_Handler(TIM_TypeDef *TIMER);
		static void Encoder_Handler_by_Time();
			
		static float Speed[NUMBER_OF_ENCODERS];
		static float Last_Speed[NUMBER_OF_ENCODERS];
		
};

#endif
