#ifndef ENCODER_DRIVER
#define ENCODER_DRIVER
#include "GPIO.h"
#include "TIMER.h"

#define NUMBER_OF_ENCODERS 2
//#define Encoder_1	0
//#define Encoder_2 1
#define AutoReaload_Ticks 1//36000
#define Ticks_till_int (AutoReaload_Ticks+1)  //Ticks to generate an interruption

typedef enum{
	Encoder_1,
	Encoder_2,
}ENCODER_ENUM;

class Encoder : protected Timer
{
	friend class Motor;
	public:			//should be private
		GPIO EncCH1;
		GPIO EncCH2;

		void ConfigEncoder();

		static uint32_t Overflowed_Ticks[NUMBER_OF_ENCODERS];
		static uint32_t Ticks[NUMBER_OF_ENCODERS];
		static uint32_t LastTicks[NUMBER_OF_ENCODERS];
		static uint32_t Ticks_Time[NUMBER_OF_ENCODERS];
		static uint32_t LastTicks_Time[NUMBER_OF_ENCODERS];
		static uint32_t Speed[NUMBER_OF_ENCODERS];

		static TIM_TypeDef *Encoder_Timers[NUMBER_OF_ENCODERS];
		static uint8_t Number_of_Encoders;
				
	public:
		Encoder(){};					//must be used only by class composition
		Encoder(TIM_TypeDef *TIM);
		uint16_t GetEncTicks();
		uint32_t GetEncSpeed();
		bool GetEncDirection(); //ta zoado, arrumar ou testar direito
			
		static void Encoder_Initiallize();
		static void Encoder_Handler(ENCODER_ENUM enc_num);
		static void Encoder_Ticks_overflow(TIM_TypeDef *TIM);
		
};

#endif
