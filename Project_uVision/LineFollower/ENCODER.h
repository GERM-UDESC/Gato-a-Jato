#ifndef ENCODER_DRIVER
#define ENCODER_DRIVER
#include "GPIO.h"
#include "TIMER.h"

#define Max_delay_Ticks_Time 150000
#define AutoReaload_Ticks 11// for pololu encoders, if you want speed, this cannot be lower then 11
#define Ticks_till_int (AutoReaload_Ticks+1)  //Ticks to generate an interruption

#define pi 3.14159265359
#define ticksToRad pi/60


typedef enum{
	Encoder_TIM1 = 0,
	Encoder_TIM2,
	Encoder_TIM3,
	Encoder_TIM4,
	NUMBER_OF_ENCODERS,
}ENCODER_ENUM;

typedef enum{
	forward,
	backward,
}ENCODER_DIRECTION;

class Encoder : public Timer
{
	private:			//should be private
		GPIO EncCH1;
		GPIO EncCH2;

		ENCODER_ENUM encoderNumber;
		float Ticks{0};
		uint32_t lastTicks{0};
		uint32_t deltaTicks{0};
		uint32_t Ticks_Time{1};
		uint32_t LastTicks_Time{0};
		uint32_t deltaTime{1};
		uint32_t lastDeltaTime{0};
		float Speed{0};
		float Last_Speed{0};

		void ConfigEncoder();
		void Handler();

		static Encoder *encPtr[NUMBER_OF_ENCODERS];
		static bool usedEncoders[NUMBER_OF_ENCODERS];

	public:
		//Encoder(){};					//must be used only by class composition
		Encoder(TIM_TypeDef *TIM);
		Encoder(Encoder *encoder);
	
		void reset();
			
		uint32_t getTicks();
		uint32_t getDeltaTicks();
		uint32_t getTicksTime();
		uint32_t getLastTicksTime();
		uint32_t getDeltaTime();
		
		float getSpeed();
		float getLastSpeed();
		float getTeta();
		bool getDirection();

		static void Encoder_Initiallize();
		static void Encoder_Handler(ENCODER_ENUM enc);
		static void Encoder_Handler_by_Time();

};

#endif
