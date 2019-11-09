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
//#include "FOLLOWING_CONTROLER.h"
//#include "SERIAL_COMMUNICATION.h"

//#include "math.h"

//#define stepTime 1000
//#define	steps 11
//#define testTime stepTime*steps
//float xtest, ytest, vtest, wtest, pwmtest;
//float linevalue, lineangle;
//uint32_t t_ini, time, delta_time, time_test;
//uint8_t counter = 0;
//uint8_t PWM_value[12] = {0,15,22,30,40,50,60,70,80,90,100,0};


//int main()
//{
//	//-----------------------------------Initiallize static parameters----------------------
//	Timer::Timer_Initiallize();
//	Encoder::Encoder_Initiallize();
//	Motor::Motor_Initialiize();
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
//	//Motor configuration
//	Motor Motor_E(PWM_E, ENC_E, AIN2, AIN1);
//	Motor Motor_D(PWM_D, ENC_D, BIN1, BIN2);
//	
//	//Line sensor
//	Reflectance_Sensor Sensor1(ADC_CH0);
//	Reflectance_Sensor Sensor2(ADC_CH1);
//	Reflectance_Sensor Sensor3(ADC_CH2);
//	Reflectance_Sensor Sensor4(ADC_CH3);
//	Reflectance_Sensor Sensor5(ADC_CH4);
//	Reflectance_Sensor Sensor6(ADC_CH5);
//	Reflectance_Sensor Sensor7(ADC_CH6);
//	Reflectance_Sensor Sensor8(ADC_CH7);
//	Line_Sensor Sensor_Board(Sensor1, Sensor2, Sensor3, Sensor4, Sensor5, Sensor6, Sensor7, Sensor8);
//	
//	//Robot Kinematic
//	Kinematic Robot(Motor_D, Motor_E, Sensor_Board);
//	
//	//Robot Control
//	Controller RobotControl(Robot);
//	
//	//Serial communication
//	USART Serial(USART3, BD_1382400);
//	
//	Communication Interface(&RobotControl, &Serial);
//	//----------------------------------------------------------------------------------------------
//	
//	//----------------------------------Initial Conditions------------------------------------------
//	AIN2.digitalWrite(LOW);
//	AIN1.digitalWrite(LOW);
//	BIN2.digitalWrite(LOW);
//	BIN1.digitalWrite(HIGH);
//	STBY.digitalWrite(HIGH);	
//	
//	//-----------------------------------------------------------------------------------------------

//	RobotControl.Robot.reset();
//	LED_Board.tooglePin();
//	counter = 0;
//	RobotControl.Robot.motorD.pwmMotor.PWMWrite(0);
//	PWM_value[0] = 0;
//	PWM_value[1] = 50;
//	PWM_value[2] = 30;
//	PWM_value[3] = 90;
//	PWM_value[4] = 20;
//	PWM_value[5] = 50;
//	PWM_value[6] = 70;
//	PWM_value[7] = 100;
//	PWM_value[8] = 70;
//	PWM_value[9] = 40;
//	PWM_value[10] = 100;
//	PWM_value[11] = 0;
//	Interface.waitForCommand();
//	t_ini = Timer::GetTime_milisec();
//	
//	while(1)
//	{
//		if (Timer::verifyTimeInterrupt())
//		{
//			time = Timer::GetTime_milisec() - t_ini;
//			if (time > (testTime))
//			{
//				RobotControl.Robot.motorD.pwmMotor.PWMWrite(0);
//			}
//			else if (time >= ((counter+1)*stepTime))
//			{
//				counter++;
//				RobotControl.Robot.motorD.pwmMotor.PWMWrite(PWM_value[counter]);
//			}
//			Encoder::Encoder_Handler_by_Time();
//			Communication::HandlerByTime();
//			delta_time = Timer::GetTime_usec() - time;
//		}
//		pwmtest = RobotControl.Robot.motorD.pwmMotor.getWritedPWM();
//		if ((Board.SysTickGetEvent()) && (Interface.command != robotStop))
//		{
//			LED_Board.tooglePin();
//		}
//	}
//}


////Interruption Part

////Encoder 1 - Interrupt Handler			//Encoder Esquerdo
//extern "C" void TIM1_UP_IRQHandler();
////Encoder 2 - Interrupt Handler			//this timer is being used as time base for the system
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
