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

uint16_t velocidade_teste = 0;
bool direction = 0;
float motorSpeed = 0;
float leitura[8];

uint32_t time = 0;
uint32_t final_time = 0;
uint32_t delta_time = 0;

//Como gerar um erro ao tentar configurar o mesmo pino para duas funções?

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
//	GPIO AIN2(PA10, GP_OUTPUT_PUSH_PULL_2MHZ);
//	GPIO AIN1(PA11, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO STBY(PA12, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO BIN1(PA15, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO BIN2(PB3, GP_OUTPUT_PUSH_PULL_2MHZ);
	
	//PWM configurations
	//PWM PWM_E(TIM3, TIM_CH2, PARTIAL_REMAP2);
	PWM PWM_D(TIM3, TIM_CH1, PARTIAL_REMAP2);
		
	//Timer
	Timer Time_Generator(TIM2, COUNTER); //This one is dedicated to generate the time base in useconds
	
	//Encoders configuration
	//Encoder ENC_E(TIM1);
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

	
	//-----------------------------------------------------------------------------------
	
	//----------------------------------Initial Conditions------------------------------------------
//	AIN2.digitalWrite(HIGH);
//	AIN1.digitalWrite(LOW);
	STBY.digitalWrite(HIGH);
	BIN1.digitalWrite(HIGH);
	BIN2.digitalWrite(LOW);
	
	PWM_D.PWMWrite(0);
	//PWM_E.PWMWrite(0);
	//-----------------------------------------------------------------------------------------------
	
	//Tests
	Motor Motor_E(TIM3, TIM_CH2, PARTIAL_REMAP2, TIM1, PA10, PA11);
	Motor_E.Set_Speed(500);
//	for (uint32_t j = 0; j < 500000; j++)
//	{
//		Sensor_Board.Calibrate_Sensor();
//		Sensor_Line_D.Calib_Reflectance_Sensor();
//		Sensor_Line_E.Calib_Reflectance_Sensor();
//		Sensor_Line_0.Calib_Reflectance_Sensor();
//		Sensor_Line_1.Calib_Reflectance_Sensor();
//		Sensor_Line_2.Calib_Reflectance_Sensor();
//		Sensor_Line_3.Calib_Reflectance_Sensor();
//		Sensor_Line_4.Calib_Reflectance_Sensor();
//		Sensor_Line_5.Calib_Reflectance_Sensor();
//		Sensor_Line_6.Calib_Reflectance_Sensor();
//		Sensor_Line_7.Calib_Reflectance_Sensor();
//	}
	
	
	//Motor_E.Set_Speed(500);
	
	
	
	while(1)
	{
		time = Timer::GetTime_usec();
		
		Encoder::Encoder_Handler();
//		leitura[0] = Sensor_Board.Read_Sensor();
//		leitura[0] = Sensor_Line_0.Reflectance_Read();
//		leitura[1] = Sensor_Line_1.Reflectance_Read();
//		leitura[2] = Sensor_Line_2.Reflectance_Read();
//		leitura[3] = Sensor_Line_3.Reflectance_Read();
//		leitura[4] = Sensor_Line_4.Reflectance_Read();
//		leitura[5] = Sensor_Line_5.Reflectance_Read();
//		leitura[6] = Sensor_Line_6.Reflectance_Read();
//		leitura[7] = Sensor_Line_7.Reflectance_Read();
		
		
		motorSpeed = ENC_D.GetEncSpeed();	
		//motorSpeed = Motor_E.Get_Speed();
		Motor_E.Handler();
		PWM_D.PWMWrite(0);
		
//		if (motorSpeed < 400) velocidade_teste++;
//		else if (motorSpeed > 450) velocidade_teste--;
//		if (velocidade_teste>65000) velocidade_teste = 65000;
//		else if (velocidade_teste<10) velocidade_teste = 10;
//		PWM_E.PWMWrite(velocidade_teste);
//		PWM_D.PWMWrite(velocidade_teste);

		if (Board.SysTickGetEvent()) 
		{
			LED_Board.tooglePin();
		}
		final_time = Timer::GetTime_usec();
		delta_time = final_time - time;
	}
}



//Timer generator interruption handler
extern "C" void TIM2_IRQHandler();

void TIM2_IRQHandler()
{
	TIM2->SR &= ~(1<<0);
	Timer::Timer_Handler_by_Time();
};

//Encoder Esquerdo - Interrupt Handler
extern "C" void TIM1_UP_IRQHandler();

void TIM1_UP_IRQHandler()
{
	TIM1->SR &= ~(1<<0);
	Encoder::Encoder_Ticks_overflow(TIM1);
};


//Encoder Direito - Interrupt Handler
extern "C" void TIM4_IRQHandler();

void TIM4_IRQHandler()
{
	TIM4->SR &= ~(1<<0);
	Encoder::Encoder_Ticks_overflow(TIM4);
};








