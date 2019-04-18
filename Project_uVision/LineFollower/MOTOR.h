#ifndef MOTOR_H
#define MOTOR_H

#include "PWM.h"
#include "ENCODER.h"

#define rpmToRads 2*pi/60
#define rpmToV rpmToRads*r
#define radsToRpm 60/(2*pi);
#define r 0.016

#define desired_size 3							
#define k (desired_size-1)
//#define Number_of_Motor 4		//the same as encoderes


#define K 792.7
#define P 22.82

#define ts 0.15 							//tempo de assentamento
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
		float U[desired_size]{0};	
		float E[desired_size]{0};			
		float Speed_Reference{0};
			
		static Motor *motPtr[Number_of_Motor];
		void Handler();

	public:
		Motor(PWM pwmMotor, Encoder encoder, GPIO In1, GPIO In2);
		Motor(Motor *motor);
	
		void reset();
		
		void Set_Speed(float Speed_Reference);  //Set the desired speed in RPM
		float Get_Speed();
		float getDistance();
		float getDeltaDistance();
		float getSpeedRadS();
		float getU();
		float getE();
		float getTeta();

		static void Motor_Initialiize();
		static void Motor_Handler_by_time();

};






#endif
