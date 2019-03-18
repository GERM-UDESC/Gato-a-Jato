#include "MOTOR.h"
	
Motor *Motor::Ptr[Number_of_Motor];

void Motor::Motor_Initialiize()
{
	for (uint8_t i = 0; i < Number_of_Motor; i++)
	{
		Motor::Ptr[i] = (Motor*)0;
	}	
}

void Motor::Motor_Handler_by_time()
{
	Motor::Ptr[Motor_1]->Handler();
	Motor::Ptr[Motor_4]->Handler();
}

Motor::Motor(PWM PWM_Motor, Encoder enc, GPIO IN1, GPIO IN2)
: pwmMotor(PWM_Motor), encoder(enc), IN1(IN1), IN2(IN2)
{

	encoder.ConfigEncoder();
	
	if 			(encoder.GetTim() == TIM1)	Motor_number = Motor_1;
	else if (encoder.GetTim() == TIM2)	Motor_number = Motor_1;
	else if (encoder.GetTim() == TIM3)	Motor_number = Motor_3;
	else if (encoder.GetTim() == TIM4)	Motor_number = Motor_4;
	Motor::Ptr[Motor_number] = this;
	
	Set_Speed(0);
	for (uint8_t i = 0; i < desired_size; i++)
	{
		U[i] = 0;				
	}	
	
};

  //configuração pinos Ponte H
  // HIGH HIGH            ---> "freio"
  // HIGH LOW or LOW HIGH ---> troca os sentidos
  // LOW LOW              ---> Para
  // STBY tem q ser HIGH para ligar a ponte H, se for LOW vai entrar em modo de stand by

void Motor::Set_Speed(int16_t Speed_Reference)
{
	this->Speed_Reference = Speed_Reference;
};

float Motor::Get_Speed()
{
	return encoder.getSpeed();	
}

void Motor::Handler()
{
	E[k] = Speed_Reference - Get_Speed();
	U[k] = ((2*KP+KI*Ts)*E[k] + (KI*Ts-2*KP)*E[k-1] + 2*U[k-1])/2;
	if(U[k] < 0)
	{
		IN1.digitalWrite(LOW);
		IN2.digitalWrite(HIGH);
		if (U[k] < -100) U[k] = -100; //satura
	}
	else if(U[k] >= 0)
	{
		IN1.digitalWrite(HIGH);
		IN2.digitalWrite(LOW);
		if (U[k] > 100) U[k] = 100; //satura
	}
	
	pwmMotor.PWMWrite(U[k]);
	
	for (int i = 0; i < k; i++)
	{
		U[i] = U[i+1];
		E[i] = E[i+1];
	}

}







