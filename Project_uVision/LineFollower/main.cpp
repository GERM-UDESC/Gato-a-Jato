//////#include "stm32f10x.h" // comentar para tirar os arquivos que eu não fiz do programa
//////#include "core_cm3.h"

////#include "Micro.h"
////#include "SysClock.h"
////#include "GPIO.h"
////#include "TIMER.h"
////#include "PWM.h"
////#include "ENCODER.h"
////#include "ADC.h"
////#include "REFLECTANCE_SENSOR.h"
////#include "LINE_SENSOR.h"
//////#include "MOTOR.h"
////#include "USART.h"

////#define number_of_points 200
////#define dead_zone 5.5

////uint32_t time = 0;
////uint32_t final_time = 0;
////uint32_t delta_time = 0;
////uint16_t Speed_points[number_of_points];
////uint32_t counter_points;
////uint16_t finished = 0;

////int main()
////{
////	//-----------------------------------Initiallize static parameters----------------------
////	Timer::Timer_Initiallize();
////	Encoder::Encoder_Initiallize();
////	
////	//----------------------------------------Setup----------------------------------------
////	SysClock Board;		//initiallize the board clock
////	
////	//Board LED
////	GPIO LED_Board(PC13, GP_OUTPUT_PUSH_PULL_2MHZ);
////	
////	//H bridge configuration
////	GPIO AIN2(PA10, GP_OUTPUT_PUSH_PULL_2MHZ);
////	GPIO AIN1(PA11, GP_OUTPUT_PUSH_PULL_2MHZ);
////	GPIO STBY(PA12, GP_OUTPUT_PUSH_PULL_2MHZ);
////	GPIO BIN1(PA15, GP_OUTPUT_PUSH_PULL_2MHZ);
////	GPIO BIN2(PB3, GP_OUTPUT_PUSH_PULL_2MHZ);
////	
////	//PWM configurations
////	PWM PWM_E(TIM3, TIM_CH2, PARTIAL_REMAP2);
////	PWM PWM_D(TIM3, TIM_CH1, PARTIAL_REMAP2);
////		
////	//Timer
////	Timer Time_Generator(TIM2, COUNTER); //This one is dedicated to generate the time base in useconds
////	
////	//Encoders configuration
////	Encoder ENC_E(TIM1);
////	Encoder ENC_D(TIM4);
////	
////	//Sensors
////	Line_Sensor Sensor_Board(ADC_CH0, ADC_CH1, ADC_CH2, ADC_CH3, ADC_CH4, ADC_CH5, ADC_CH6, ADC_CH7);
//////	Reflectance_Sensor Sensor_Line_0(ADC_CH0);
//////	Reflectance_Sensor Sensor_Line_1(ADC_CH1);
//////	Reflectance_Sensor Sensor_Line_2(ADC_CH2);
//////	Reflectance_Sensor Sensor_Line_3(ADC_CH3);
//////	Reflectance_Sensor Sensor_Line_4(ADC_CH4);
//////	Reflectance_Sensor Sensor_Line_5(ADC_CH5);
//////	Reflectance_Sensor Sensor_Line_6(ADC_CH6);
//////	Reflectance_Sensor Sensor_Line_7(ADC_CH7);
//////	Reflectance_Sensor Sensor_Line_D(ADC_CH8);	

////	USART Serial(USART3, BD_250000);
////	
////	//----------------------------------------------------------------------------------------------
////	
////	//----------------------------------Initial Conditions------------------------------------------
////	AIN2.digitalWrite(HIGH);
////	AIN1.digitalWrite(LOW);
////	STBY.digitalWrite(HIGH);
////	BIN1.digitalWrite(HIGH);
////	BIN2.digitalWrite(LOW);
////	
////	PWM_D.PWMWrite(0);
////	PWM_E.PWMWrite(0);
////	//-----------------------------------------------------------------------------------------------
////			

////	while(1)
////	{
////		while ((Encoder::Speed[Encoder_TIM1] > 0) || (Encoder::Speed[Encoder_TIM4] > 0) || (Timer::GetTime_usec() < 1000000));
////		counter_points = 0;
////		finished = 0;
////				
////		PWM_E.PWMWrite(dead_zone);	
////		PWM_D.PWMWrite(dead_zone);	
////		
////		for (uint8_t i = 0; i < 10; i++)
////		{
////			//PWM_E.PWMWrite((Max_PWM/10)*(i));
////			PWM_D.PWMWrite(10*i+dead_zone);
////			PWM_E.PWMWrite(10*i+dead_zone);
////			while (finished == 0);
////			Serial.Send_Vec_16(&Speed_points[0],number_of_points);
////			counter_points = 0;
////			finished = 0;
////			if (i == 10) finished = 1;
////		}	
////		PWM_E.PWMWrite(0);	//turn off the motor
////		PWM_D.PWMWrite(0);	//turn off the motor
////		
////		while(1)
////		{
////			
////			if (Board.SysTickGetEvent()) 
////			{
//////				Serial.Send(0);
////				LED_Board.tooglePin();
////			}
////		}
////	}
////}

//////Timer generator interruption handler
////extern "C" void TIM2_IRQHandler();

////void TIM2_IRQHandler()
////{
////	TIM2->SR &= ~(1<<0);
////	Timer::Timer_Handler();
////	Encoder::Encoder_Handler_by_Time();
////	if ((counter_points < number_of_points) &&  (finished == 0))
////	{
////		Speed_points[counter_points] = (uint16_t)Encoder::Speed[Encoder_TIM4];
////		counter_points++;
////		if (counter_points == number_of_points) finished = 1;
////	}
////};

//#include "Micro.h"
//#include "SysClock.h"
//#include "GPIO.h"
//#include "TIMER.h"
//#include "PWM.h"
//#include "ENCODER.h"
//#include "ADC.h"
//#include "REFLECTANCE_SENSOR.h"
//#include "LINE_SENSOR.h"
//#include "MOTOR.h"
//#include "USART.h"
//#include "KINEMATIC_CONTROL.h"

//#include "math.h"

//#define dead_zone 5.5

//uint16_t number_of_points;
//float Ref;
//float Refw;
//float Ref1;
//bool sending = 0;
//bool flag;
//float u_teste;
//float u_D, u_E;
//float speed_teste;
//float speed_d, speed_e, speedV, speedW, speed_temp;
//float xtest, ytest, tetatest;
//float testLine[9];
//uint32_t counter = 0;
//float time, delta_time;


//int main()
//{
//	//-----------------------------------Initiallize static parameters----------------------
//	Timer::Timer_Initiallize();
//	Encoder::Encoder_Initiallize();
//	
//	//----------------------------------------Setup----------------------------------------
//	SysClock Board;		//initiallize the board clock
//	
//	//Board LED
//	GPIO LED_Board(PC13, GP_OUTPUT_PUSH_PULL_2MHZ);
//	
//	//Timer
//	Timer Time_Generator(TIM2, COUNTER); //This one is dedicated to generate the time base in useconds
//	
//	//H bridge configuration
//	GPIO STBY(PA12, GP_OUTPUT_PUSH_PULL_2MHZ);
//	GPIO AIN2(PA10, GP_OUTPUT_PUSH_PULL_2MHZ);
//	GPIO AIN1(PA11, GP_OUTPUT_PUSH_PULL_2MHZ);
//	GPIO BIN1(PA15, GP_OUTPUT_PUSH_PULL_2MHZ);
//	GPIO BIN2(PB3, GP_OUTPUT_PUSH_PULL_2MHZ);
//	AIN2.digitalWrite(LOW);
//	AIN1.digitalWrite(LOW);
//	BIN2.digitalWrite(LOW);
//	BIN1.digitalWrite(LOW);
//	STBY.digitalWrite(HIGH);				
//		
//	//PWM configurations
//	PWM PWM_E(TIM3, TIM_CH2, PARTIAL_REMAP2);
//	PWM PWM_D(TIM3, TIM_CH1, PARTIAL_REMAP2);
//	PWM_E.PWMWrite(0);
//	PWM_D.PWMWrite(0);
//	
//	//Encoders configuration
//	Encoder ENC_E(TIM1);
//	Encoder ENC_D(TIM4);
//	
//	//Serial communication
//	USART Serial(USART3, BD_1000000);
//	
//	//----------------------------------------------------------------------------------------------
//	
//	//----------------------------------Initial Conditions------------------------------------------
//	AIN2.digitalWrite(HIGH);
//	AIN1.digitalWrite(LOW);
//	BIN1.digitalWrite(HIGH);
//	BIN2.digitalWrite(LOW);
//	
//	PWM_D.PWMWrite(0);
//	PWM_E.PWMWrite(0);
//	STBY.digitalWrite(HIGH);

//	//-----------------------------------------------------------------------------------------------

//	counter = 0;
//	number_of_points = 10*Serial.Receive();
//	sending = 1;
//	ENC_D.reset();
//	ENC_E.reset();
//	while(Timer::GetTime_usec() < 2000000);
//	Ref = 0;

//	while(1)
//	{
//		time = Timer::GetTime_usec();
//		while(flag == 0)
//		{
//			if (Serial.Available())
//			{
//				Ref = Serial.Receive();	//in %
//				PWM_D.PWMWrite(Ref+dead_zone);
//				PWM_E.PWMWrite(Ref+dead_zone);
//				counter = 0;
//			}
//		}

//		if (sending) 	//sending in open loop
//		{
//			if (counter <= number_of_points)
//			{
//				counter++;
//				Serial.sendFloat(&Ref);
//				speed_d = ENC_D.getSpeed();
//				speed_e = ENC_E.getSpeed();
//				Serial.sendFloat(&speed_d);
//				Serial.sendFloat(&speed_e);
//			}
//		}
//		
//		flag = 0;
//		if (Board.SysTickGetEvent()) 
//		{
//			LED_Board.tooglePin();
//		}
//	}
//}


////Interruption Part

////Encoder 1 - Interrupt Handler			//Encoder Esquerdo
//extern "C" void TIM1_UP_IRQHandler();
//////Encoder 2 - Interrupt Handler		//this timer is being used as time base for the system
//extern "C" void TIM2_IRQHandler();
////Encoder 3 - Interrupt Handler			//PWM generator
//extern "C" void TIM3_IRQHandler();
////Encoder 4 - Interrupt Handler			//Encoder direito
//extern "C" void TIM4_IRQHandler();

//void TIM1_UP_IRQHandler()
//{
//	TIM1->SR &= ~(1<<0);
//	Encoder::Encoder_Handler(Encoder_TIM1);
//};

//void TIM2_IRQHandler()
//{
//	TIM2->SR &= ~(1<<0);
//	Timer::Timer_Handler();
//	Encoder::Encoder_Handler_by_Time();
//	flag = 1;
//};

//void TIM3_IRQHandler()
//{
//	TIM3->SR &= ~(1<<0);
//};

//void TIM4_IRQHandler()
//{
//	TIM4->SR &= ~(1<<0);
//	Encoder::Encoder_Handler(Encoder_TIM4);
//};
