//#include "stm32f10x.h" // comentar para tirar os arquivos que eu n�o fiz do programa
//#include "core_cm3.h"

#include "Micro.h"
#include "SysClock.h"
#include "GPIO.h"
#include "TIMER.h"
#include "PWM.h"
#include "ENCODER.h"
#include "ADC.h"
#include "REFLECTANCE_SENSOR.h"
#include "LINE_SENSOR.h"
#include "MOTOR.h"
#include "USART.h"

#define number_of_points 800

uint32_t time = 0;
uint32_t final_time = 0;
uint32_t delta_time = 0;
uint16_t Speed_points[number_of_points];
uint32_t counter_points;
uint16_t finished = 0;
uint16_t test = 0;
uint16_t test1 = 0;
//uint16_t test_usart[1000];


//as vari�veis n�o est�o zerando, pq?


int main()
{
	//-----------------------------------Initiallize static parameters----------------------
	Timer::Timer_Initiallize();
	Encoder::Encoder_Initiallize();
	
	//----------------------------------------Setup----------------------------------------
	SysClock Board;		//initiallize the board clock
	
	//Board LED
	GPIO LED_Board(PC13, GP_OUTPUT_PUSH_PULL_2MHZ);
	
	//H bridge configuration
	GPIO AIN2(PA10, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO AIN1(PA11, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO STBY(PA12, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO BIN1(PA15, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO BIN2(PB3, GP_OUTPUT_PUSH_PULL_2MHZ);
	
	//PWM configurations
	PWM PWM_E(TIM3, TIM_CH2, PARTIAL_REMAP2);
	PWM PWM_D(TIM3, TIM_CH1, PARTIAL_REMAP2);
		
	//Timer
	Timer Time_Generator(TIM2, COUNTER); //This one is dedicated to generate the time base in useconds
	
	//Encoders configuration
	Encoder ENC_E(TIM1);
	Encoder ENC_D(TIM4);
	
	//Sensors
	Line_Sensor Sensor_Board(ADC_CH0, ADC_CH1, ADC_CH2, ADC_CH3, ADC_CH4, ADC_CH5, ADC_CH6, ADC_CH7);
//	Reflectance_Sensor Sensor_Line_0(ADC_CH0);
//	Reflectance_Sensor Sensor_Line_1(ADC_CH1);
//	Reflectance_Sensor Sensor_Line_2(ADC_CH2);
//	Reflectance_Sensor Sensor_Line_3(ADC_CH3);
//	Reflectance_Sensor Sensor_Line_4(ADC_CH4);
//	Reflectance_Sensor Sensor_Line_5(ADC_CH5);
//	Reflectance_Sensor Sensor_Line_6(ADC_CH6);
//	Reflectance_Sensor Sensor_Line_7(ADC_CH7);
//	Reflectance_Sensor Sensor_Line_D(ADC_CH8);	

	USART Serial(USART3);
	

	
	//----------------------------------------------------------------------------------------------
	
	//----------------------------------Initial Conditions------------------------------------------
	AIN2.digitalWrite(HIGH);
	AIN1.digitalWrite(LOW);
	STBY.digitalWrite(HIGH);
	BIN1.digitalWrite(HIGH);
	BIN2.digitalWrite(LOW);
	
	PWM_D.PWMWrite(0);
	PWM_E.PWMWrite(0);
	//-----------------------------------------------------------------------------------------------
			
	
	while(1)
	{
		
		while(1)
		{
			time = Timer::GetTime_usec();
		}
		
		counter_points = 0;
		finished = 0;
		for (uint8_t i = 0; i < 11; i++)
		{
			PWM_E.PWMWrite(6553*(i));
			while (finished == 0);
			Serial.Send_Vec_16(&Speed_points[0],number_of_points);
			counter_points = 0;
			finished = 0;
		}
		
//		counter_points = 0;
//		finished = 0;
//		test = 0;
//		while (finished == 0)
//		{
//			if (counter_points > test*(number_of_points/10))
//			{
//				test++;
//				if (test > 10) test = 10;
//				PWM_E.PWMWrite(6553*(test));
//			}
//		}
		PWM_E.PWMWrite(0);	//turn off the motor
//		
//		
//		Serial.Send_Vec_16(&Speed_points[0],number_of_points);
		
		
		
		
		
		//Serial.Receive();
//		while(1)
//		{
//			if (Board.SysTickGetEvent()) 
//			{
//				LED_Board.tooglePin();
//			}
//			Encoder::Encoder_Handler();
//			test = ENC_E.GetEncSpeed();
//			test1 = ENC_E.GetEncTicks();
//			
//		}
		final_time = Timer::GetTime_usec();
		delta_time = final_time - time;
		while(1)
		{
			test = ENC_E.GetEncTicks();
			test1 = ENC_E.GetEncSpeed();
		}
	}
}

//Timer generator interruption handler
extern "C" void TIM2_IRQHandler();

void TIM2_IRQHandler()
{
	TIM2->SR &= ~(1<<0);
	Timer::Timer_Handler_by_Time();
	if ((counter_points < number_of_points) &&  (finished == 0))
	{
		Speed_points[counter_points] = (uint16_t)Encoder::Speed[Encoder_1];
		counter_points++;
		if (counter_points == number_of_points) finished = 1;
	}
	
};

//Encoder Esquerdo - Interrupt Handler
extern "C" void TIM1_UP_IRQHandler();

void TIM1_UP_IRQHandler()
{
	TIM1->SR &= ~(1<<0);
		time = Timer::GetTime_usec();
	Encoder::Encoder_Ticks_overflow(TIM1);
	Encoder::Encoder_Handler(Encoder_1);
	final_time = Timer::GetTime_usec();
	delta_time = final_time - time;
};


//Encoder Direito - Interrupt Handler
extern "C" void TIM4_IRQHandler();

void TIM4_IRQHandler()
{
	TIM4->SR &= ~(1<<0);
	Encoder::Encoder_Ticks_overflow(TIM4);
	Encoder::Encoder_Handler(Encoder_2);
};








