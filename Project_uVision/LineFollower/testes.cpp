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

#define number_of_points 2000

int32_t U[3] = {0,0,0};
int32_t E[3] = {0,0,0};
int32_t Ref = 10;
uint16_t flag = 1;
int32_t u_teste = 0;
int32_t e_teste = 0;
float speed_teste = 0;
uint32_t counter = 0;
uint32_t time = 0;

int main()
{
	//-----------------------------------Initiallize static parameters----------------------
	Timer::Timer_Initiallize();
	Encoder::Encoder_Initiallize();
	Motor::Motor_Initialiize();
	
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
	
	//Motor configuratio
	Motor Motor_D(TIM3, TIM_CH1, PARTIAL_REMAP2, TIM4, PA11, PA10);
	
	//PWM configurations
	PWM PWM_E(TIM3, TIM_CH2, PARTIAL_REMAP2);
	//PWM PWM_D(TIM3, TIM_CH1, PARTIAL_REMAP2);
		
	//Timer
	Timer Time_Generator(TIM2, COUNTER); //This one is dedicated to generate the time base in useconds
	
	//Encoders configuration
	Encoder ENC_E(TIM1);
	//Encoder ENC_D(TIM4);
	
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

	USART Serial(USART3, BD_250000);
	
	//----------------------------------------------------------------------------------------------
	
	//----------------------------------Initial Conditions------------------------------------------
	AIN2.digitalWrite(HIGH);
	AIN1.digitalWrite(LOW);
	STBY.digitalWrite(HIGH);
	BIN1.digitalWrite(HIGH);
	BIN2.digitalWrite(LOW);
	
	//PWM_D.PWMWrite(0);
	PWM_E.PWMWrite(0);
	//-----------------------------------------------------------------------------------------------
	
	for (int i = 0; i < 3; i++)
	{
		U[i] = 0;
		E[i] = 0;
	}
	Ref = 1000;
	counter = 0;
	while(Timer::GetTime_usec() < 2000000);
	Motor_D.Set_Speed(1500);
	while(1)
	{
		while(flag == 0);
		counter++;
		Motor_D.Handler();
		speed_teste = Motor_D.Get_Speed();
		u_teste = Motor_D.U[k];
		e_teste = Motor::E[Motor_4][k];
		flag = 0;
//		U[2] = (2*KP +KI*Ts)*E[2]+(KI*Ts - 2*KP)*E[1]+U[0] + dead_zone;	
//		U[2] = ((2*KP+KI*Ts)*E[2] + (KI*Ts-2*KP)*E[1] + 2*U[1])/2 + dead_zone;		
	
//		Serial.Send_Vec_16(&speed_teste,1);
//		if (counter > 2*ts/Ts)
//		{
//			PWM_D.PWMWrite(0);
//			while(1);
//		}
	}
}

//Timer generator interruption handler
extern "C" void TIM2_IRQHandler();

void TIM2_IRQHandler()
{
	TIM2->SR &= ~(1<<0);
	Timer::Timer_Handler();
	Encoder::Encoder_Handler_by_Time();
	Motor::Motor_Handler_by_time();
	flag = 1;
};

