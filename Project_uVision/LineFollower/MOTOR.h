#ifndef MOTOR_H
#define MOTOR_H

#include "PWM.h"
#include "ENCODER.h"

#define desired_size 3							
#define k (desired_size-1)
#define Number_of_Motor 4		//the same as encoderes

#define dead_zone 7
#define KP 0.0308
#define KI 0.7520
#define Ts Time_between_int/1000000
#define ts 0.15

typedef enum{
	Motor_1,
	Motor_2,
	Motor_3,
	Motor_4,
}MOTOR_ENUM;

class Motor
{
public:
	PWM PWM_Motor;
	Encoder Encoder_Motor;
	GPIO IN1;
	GPIO IN2;
	MOTOR_ENUM Motor_number;
	int16_t U[desired_size];																			//Control action
	static int16_t Speed_Reference[Number_of_Motor];
	static int16_t E[Number_of_Motor][desired_size];				//Error

public:
	Motor(TIM_TypeDef *TIM_PWM, TIM_CHANNELS channel_PWM, TIM_REMAP PWMremap, TIM_TypeDef *TIM_ENCODER, GPIO_IO_ENUM IO_Pin_IN1, GPIO_IO_ENUM IO_Pin_IN2);
	void Set_Speed(int16_t Speed_Reference);  //Set the desired speed in RPM
	uint32_t Get_position();
	float Get_Speed();
	void Handler();

	static void Motor_Initialiize();
	static void Motor_Handler_by_time();

};






#endif
