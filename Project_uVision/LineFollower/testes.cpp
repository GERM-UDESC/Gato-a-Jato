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
float Ref1;
bool sending = 0;
bool flag;
float u_teste;
float u_D, u_E;
float speed_teste;
float speed_d, speed_e, speedV, speedW, speed_temp;
float xtest, ytest, tetatest;
float testLine[9];
uint32_t counter = 0;
float time, delta_time;


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
	GPIO STBY(PA12, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO AIN2(PA10, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO AIN1(PA11, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO BIN1(PA15, GP_OUTPUT_PUSH_PULL_2MHZ);
	GPIO BIN2(PB3, GP_OUTPUT_PUSH_PULL_2MHZ);
	AIN2.digitalWrite(LOW);
	AIN1.digitalWrite(LOW);
	BIN2.digitalWrite(LOW);
	BIN1.digitalWrite(LOW);
	STBY.digitalWrite(HIGH);				
		
	//PWM configurations
	PWM PWM_E(TIM3, TIM_CH2, PARTIAL_REMAP2);
	PWM PWM_D(TIM3, TIM_CH1, PARTIAL_REMAP2);
	PWM_E.PWMWrite(0);
	PWM_D.PWMWrite(0);
	
	//Encoders configuration
	Encoder ENC_E(TIM1);
	Encoder ENC_D(TIM4);
	
	//Motor configuration
	Motor Motor_E(PWM_E, ENC_E, AIN2, AIN1);
	Motor Motor_D(PWM_D, ENC_D, BIN1, BIN2);
	
	//Robot Kinematic
	Kinematic Robot(Motor_D, Motor_E);
	
	//Line sensor
	Reflectance_Sensor Sensor1(ADC_CH0);
	Reflectance_Sensor Sensor2(ADC_CH1);
	Reflectance_Sensor Sensor3(ADC_CH2);
	Reflectance_Sensor Sensor4(ADC_CH3);
	Reflectance_Sensor Sensor5(ADC_CH4);
	Reflectance_Sensor Sensor6(ADC_CH5);
	Reflectance_Sensor Sensor7(ADC_CH6);
	Reflectance_Sensor Sensor8(ADC_CH7);
	Line_Sensor Sensor_Board(Sensor1, Sensor2, Sensor3, Sensor4, Sensor5, Sensor6, Sensor7, Sensor8);

	//Serial communication
	USART Serial(USART3, BD_1000000);
	
	//----------------------------------------------------------------------------------------------
	
	//----------------------------------Initial Conditions------------------------------------------
	STBY.digitalWrite(HIGH);

	//-----------------------------------------------------------------------------------------------

	counter = 0;
	//number_of_points = 10*Serial.Receive();
	sending = 1;
	Robot.reset();
	while(Timer::GetTime_usec() < 2000000);
	Robot.reset();
	Ref = 0.5;
	Refw = 0;
	Ref1 = 0;
	Robot.setRobotSpeed(Ref, Refw);
	
//	Sensor_Board.Calibrate_Sensor(100000);
	
	while(1)
	{
//		time = Timer::GetTime_usec();
//		while(flag == 0)
//		{
//			if (Serial.Available())
//			{
//				Ref = 10*Serial.Receive();	//in RPM
//				Ref1 = Ref;
//				Ref = Ref*rpmToRads*r;			
//				Robot.setRobotSpeed(Ref,0);
//				counter = 0;
//			}
//		}
//		if (Timer::GetTime_usec() > 3000000) while(1);
//		speed_e = Robot.motorE.Get_Speed();
		speed_d = Robot.motorD.Get_Speed();
		xtest = Robot.getX();
		ytest = Robot.getY();
		tetatest = Robot.getTeta();
		if (xtest > 1) 
		{
			Robot.setRobotSpeed(0,0);
			while(1)
			{
				xtest = Robot.getX();
				if (xtest > 1.02) Robot.setRobotSpeed(-0.5,0);
				if ((xtest < 1.02) && (xtest > 0.98)) Robot.setRobotSpeed(0,0);
				if (xtest > 0.98) Robot.setRobotSpeed(0.5,0);
			}
		}

		
//		if ((speed_d > 3000) )
//		{
//			speed_d = Robot.motorD.encoder.getDeltaTime();
//		}
		
//		if (sending) 
//		{
////			if (counter <= number_of_points)
////			{
////				counter++;
////				Serial.sendFloat(&Ref1);
//				speed_teste = Robot.motorD.Get_Speed();
//				Serial.sendFloat(&speed_teste);
////				u_teste = Robot.motorD.getU();
////				Serial.sendFloat(&u_teste);
////				speed_teste = Robot.motorE.Get_Speed();
////				Serial.sendFloat(&speed_teste);
////				u_teste = Robot.motorE.getU();
////				Serial.sendFloat(&u_teste);
////			}
//		}
//		flag = 0;
//		testLine[8] = Sensor_Board.Read_Sensor();
//		for(int i = 0; i < 8; i++)
//		{
//			testLine[i] = Sensor_Board.Sensors[i].Reflectance_Read();
//		}
		if (Board.SysTickGetEvent()) 
		{
			LED_Board.tooglePin();
		}
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
	Kinematic::handlerByTime();
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
