#ifndef MOTOR_H
#define MOTOR_H

#include "PWM.h"
#include "ENCODER.h"

class Motor
{
private:
	PWM PWM_Motor;
	Encoder Encoder_Motor;
	GPIO IN1;
	GPIO IN2;
public:
	int32_t motor_PWM; //This variable saves the actual PWM value written in the motor
	int16_t desired_speed;

public:
	Motor(TIM_TypeDef *TIM_PWM, TIM_CHANNELS channel_PWM, TIM_REMAP PWMremap, TIM_TypeDef *TIM_ENCODER, GPIO_IO_ENUM IO_Pin_IN1, GPIO_IO_ENUM IO_Pin_IN2);
	void Set_Position(uint32_t desired_ticks);
	void Set_Speed(int16_t Speed_Reference);  //Set the desired speed in RPM
	uint32_t Get_position();
	float Get_Speed();
	void Handler();


};






#endif
