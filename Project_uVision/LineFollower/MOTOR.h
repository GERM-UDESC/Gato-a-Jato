#ifndef MOTOR_H
#define MOTOR_H

#include "PWM.h"
#include "ENCODER.h"

#define desired_size 3							
#define k (desired_size-1)
//#define Number_of_Motor 4		//the same as encoderes

#define dead_zone 0

#define K 792.7
#define P 22.82

#define ts 0.15 //tempo de assentamento
#define KP 4/(K*ts)
#define KI P*KP
#define Ts Time_between_int/1000000


typedef enum{
	Motor_1,
	Motor_2,
	Motor_3,
	Motor_4,
	Number_of_Motor,
}MOTOR_ENUM;

class Motor
{
	public:
		PWM pwmMotor;
		Encoder encoder;
		GPIO IN1;
		GPIO IN2;
	
		MOTOR_ENUM Motor_number;
		float U[desired_size];	
		float E[desired_size];			
		int16_t Speed_Reference;
			
		static Motor *Ptr[Number_of_Motor];
		void Handler();

	public:
		Motor(PWM pwmMotor, Encoder enc, GPIO IN1, GPIO IN2);
		void Set_Speed(int16_t Speed_Reference);  //Set the desired speed in RPM
		uint32_t Get_position();
		float Get_Speed();
		

		static void Motor_Initialiize();
		static void Motor_Handler_by_time();

};






#endif
