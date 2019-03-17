#ifndef ENCODER_DRIVER
#define ENCODER_DRIVER
#include "GPIO.h"
#include "TIMER.h"

#define min_rpm_precision 30
#define Max_speed_variation 500
#define Max_delay_Ticks_Time (500000/min_rpm_precision)	//This value is used to make shure that the motor speed i'll go to zero
#define AutoReaload_Ticks 11// for pololu encoders, if you want speed, this cannot be lower then 11
#define Ticks_till_int (AutoReaload_Ticks+1)  //Ticks to generate an interruption

/*
	If you want to change the timer used for time base and use it as encoder, just uncomment the lines of the actuall time base timer
	and comment the line of the new time base timer (the interrupt handling lines)
*/

typedef enum{
	Encoder_TIM1 = 0,
	Encoder_TIM2,
	Encoder_TIM3,
	Encoder_TIM4,
	NUMBER_OF_ENCODERS,
}ENCODER_ENUM;

class Encoder : protected Timer
{
	friend class Motor;
	private:			//should be private
		GPIO EncCH1;
		GPIO EncCH2;

		ENCODER_ENUM encoderNumber;
		uint32_t Ticks;
		uint32_t Ticks_Time;
		uint32_t LastTicks_Time;
		float Speed;
		float Last_Speed;

		void ConfigEncoder();
		void Handler();

		static Encoder *Ptr[NUMBER_OF_ENCODERS];
		static bool usedEncoders[NUMBER_OF_ENCODERS];

	public:
		Encoder(){};					//must be used only by class composition
		Encoder(TIM_TypeDef *TIM);
		uint16_t GetEncTicks();
		float GetEncSpeed();

		static void Encoder_Initiallize();
		static void Encoder_Handler(ENCODER_ENUM enc);
		static void Encoder_Handler_by_Time();

};

#endif
