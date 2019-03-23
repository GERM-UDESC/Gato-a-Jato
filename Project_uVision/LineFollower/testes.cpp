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
#include "KINEMATIC_CONTROL.h"

#include "math.h"

uint16_t number_of_points;
float Ref;
float Refw;
uint16_t Ref16;
bool sending = 0;
bool direction;

uint16_t flag = 1;
uint8_t u_teste;
float u_D, u_E;
uint16_t e_teste = 0;
uint16_t speed_teste;
float speed_d, speed_e;
uint32_t counter = 0;
uint32_t time, delta_time;
//uint_fast32_t te;



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
	
	//Timer
	Timer Time_Generator(TIM2, COUNTER); //This one is dedicated to generate the time base in useconds
	
	//H bridge configuration
	GPIO AIN2(PA10, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO AIN1(PA11, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO STBY(PA12, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO BIN1(PA15, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO BIN2(PB3, GP_OUTPUT_PUSH_PULL_2MHZ);
		
	//PWM configurations
	PWM PWM_E(TIM3, TIM_CH2, PARTIAL_REMAP2);
	PWM PWM_D(TIM3, TIM_CH1, PARTIAL_REMAP2);
	
	//Encoders configuration
	Encoder ENC_E(TIM1);
	Encoder ENC_D(TIM4);
	
	//Motor configuration
	Motor Motor_E(PWM_E, ENC_E, AIN2, AIN1);
	Motor Motor_D(PWM_D, ENC_D, BIN1, BIN2);
	
	//Robot Kinematic
	Kinematic Robot(Motor_D, Motor_E);
	
	//Line sensor
//	Reflectance_Sensor Sensor_Line_0(ADC_CH0);
//	Reflectance_Sensor Sensor_Line_1(ADC_CH1);
//	Reflectance_Sensor Sensor_Line_2(ADC_CH2);
//	Reflectance_Sensor Sensor_Line_3(ADC_CH3);
//	Reflectance_Sensor Sensor_Line_4(ADC_CH4);
//	Reflectance_Sensor Sensor_Line_5(ADC_CH5);
//	Reflectance_Sensor Sensor_Line_6(ADC_CH6);
//	Reflectance_Sensor Sensor_Line_7(ADC_CH7);
//	Reflectance_Sensor Sensor_Line_D(ADC_CH8);	
	Line_Sensor Sensor_Board(ADC_CH0, ADC_CH1, ADC_CH2, ADC_CH3, ADC_CH4, ADC_CH5, ADC_CH6, ADC_CH7);


	USART Serial(USART3, BD_1000000);
	
	//----------------------------------------------------------------------------------------------
	
	//----------------------------------Initial Conditions------------------------------------------
	STBY.digitalWrite(HIGH);

	//-----------------------------------------------------------------------------------------------

	counter = 0;
	//number_of_points = 10*Serial.Receive();
	sending = 1;
	while(Timer::GetTime_usec() < 2000000);
	Ref = 0;
	Refw = 0;
	Ref16 = 0;
	Robot.setRobotSpeed(Ref, Refw);
	while(1)
	{
//		while(flag == 0)
//		{
//			if (Serial.Available())
//			{
//				Ref = 10*Serial.Receive();	//in RPM
//				Ref16 = (uint16_t)Ref;
//				Ref = Ref*rpmToRads*r;			
//				Robot.setRobotSpeed(Ref,0);
//				counter = 0;
//			}
//		}
		Robot.setRobotSpeed(Ref, Refw);
		speed_d = Robot.motorD.Get_Speed();
		speed_e = Robot.motorE.Get_Speed();
		u_D = Robot.motorD.getU();
		u_E = Robot.motorE.getU();
		direction = Robot.motorD.encoder.getDirection();
		time = Timer::GetTime_usec();
		
//		if (sending) 
//		{
//			if (counter <= number_of_points)
//			{
//				counter++;
//				Serial.Send_Vec_16(&Ref16, 1);
//				speed_teste = (uint16_t)Robot.motorD.Get_Speed();
//				u_teste = (uint8_t)Robot.motorD.getU();
//				Serial.Send_Vec_16(&speed_teste,1);
//				Serial.Send(u_teste);
//				speed_teste = (uint16_t)Robot.motorE.Get_Speed();
//				u_teste = (uint8_t)Robot.motorE.getU();
//				Serial.Send_Vec_16(&speed_teste,1);
//				Serial.Send(u_teste);
//			}
//		}
		flag = 0;
		delta_time = Timer::GetTime_usec() - time;
	}
}


//Interruption Part

//Encoder 1 - Interrupt Handler			//Encoder Esquerdo
extern "C" void TIM1_UP_IRQHandler();
////Encoder 2 - Interrupt Handler		//this timer is being used as time base for the system
extern "C" void TIM2_IRQHandler();
//Encoder 3 - Interrupt Handler			//PWM generator
extern "C" void TIM3_IRQHandler();
//Encoder 4 - Interrupt Handler			//Encoder direito
extern "C" void TIM4_IRQHandler();

void TIM1_UP_IRQHandler()
{
	TIM1->SR &= ~(1<<0);
	Encoder::Encoder_Handler(Encoder_TIM1);
};

void TIM2_IRQHandler()
{
	TIM2->SR &= ~(1<<0);
	Timer::Timer_Handler();
	Encoder::Encoder_Handler_by_Time();
	Motor::Motor_Handler_by_time();
	flag = 1;
};

void TIM3_IRQHandler()
{
	TIM3->SR &= ~(1<<0);
};

void TIM4_IRQHandler()
{
	TIM4->SR &= ~(1<<0);
	Encoder::Encoder_Handler(Encoder_TIM4);
};
