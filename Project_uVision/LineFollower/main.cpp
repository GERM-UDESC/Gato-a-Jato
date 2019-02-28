//#include "stm32f10x.h" // comentar para tirar os arquivos que eu não fiz do programa
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

#define number_of_points 1000

uint32_t time = 0;
uint32_t final_time = 0;
uint32_t delta_time = 0;
uint16_t Speed_points[number_of_points];
uint32_t counter_points;
uint16_t finished = 0;



//as variáveis não estão zerando, pq?


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

	USART Serial(USART3, BD_57600);
	
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
		while ((Encoder::Speed[Encoder_TIM4] > 0) || (Timer::GetTime_usec() < 1000000));
		counter_points = 0;
		finished = 0;
		for (uint8_t i = 0; i < 11; i++)
		{
			PWM_E.PWMWrite((AutoReloadPWM/10)*(i));
			PWM_D.PWMWrite((AutoReloadPWM/10)*(i));
			while (finished == 0);
			Serial.Send_Vec_16(&Speed_points[0],number_of_points);
			counter_points = 0;
			finished = 0;
			if (i == 10) finished = 1;
		}	
		
		PWM_E.PWMWrite(0);	//turn off the motor
		PWM_D.PWMWrite(0);	//turn off the motor

		while(1)
		{
			if (Board.SysTickGetEvent()) 
			{
				LED_Board.tooglePin();
			}
		}
	}
}

//Timer generator interruption handler
extern "C" void TIM2_IRQHandler();

void TIM2_IRQHandler()
{
	TIM2->SR &= ~(1<<0);
	Timer::Timer_Handler();
	Encoder::Encoder_Handler_by_Time();
	if ((counter_points < number_of_points) &&  (finished == 0))
	{
		Speed_points[counter_points] = (uint16_t)Encoder::Speed[Encoder_TIM4];
		counter_points++;
		if (counter_points == number_of_points) finished = 1;
	}
};

