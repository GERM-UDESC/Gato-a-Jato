#include "MOTOR.h"
	
Motor *Motor::motPtr[Number_of_Motor];

void Motor::Motor_Initialiize()
{
	for (uint8_t i = 0; i < Number_of_Motor; i++)
	{
		Motor::motPtr[i] = (Motor*)0;
	}	
}

void Motor::Motor_Handler_by_time()
{
	Motor::motPtr[Motor_1]->Handler();
	Motor::motPtr[Motor_4]->Handler();
}

Motor::Motor(PWM PWM_Motor, Encoder encoder, GPIO In1, GPIO In2): pwmMotor(&PWM_Motor), encoder(&encoder), IN1(&In1), IN2(&In2)
{
	if 			(this->encoder.GetTim() == TIM1)	Motor_number = Motor_1;
	else if (this->encoder.GetTim() == TIM2)	Motor_number = Motor_2;
	else if (this->encoder.GetTim() == TIM3)	Motor_number = Motor_3;
	else if (this->encoder.GetTim() == TIM4)	Motor_number = Motor_4;
	Motor::motPtr[Motor_number] = this;
	
	Set_Speed(0);
	for (uint8_t i = 0; i < desired_size; i++)
	{
		U[i] = 0;				
	}	
	
};

Motor::Motor(Motor *motor): pwmMotor(&motor->pwmMotor), encoder(&motor->encoder), IN1(&motor->IN1), IN2(&motor->IN2)
{
	this->Motor_number = motor->Motor_number;
	Motor::motPtr[Motor_number] = this;
	
	Set_Speed(0);
	for (uint8_t i = 0; i < desired_size; i++)
	{
		U[i] = 0;				
	}	
	
};

void Motor::reset()
{
	encoder.reset();
	for (int i = 0; i < desired_size; i++)
	{
		U[i] = 0;	
		E[i] = 0;		
	}	
	Speed_Reference = 0;
}

  //configuração pinos Ponte H
  // HIGH HIGH            ---> "freio"
  // HIGH LOW or LOW HIGH ---> troca os sentidos
  // LOW LOW              ---> Para
  // STBY tem q ser HIGH para ligar a ponte H, se for LOW vai entrar em modo de stand by

void Motor::Set_Speed(float Speed_Reference)
{
	this->Speed_Reference = Speed_Reference;
};

void Motor::Handler()
{
	E[k] = Speed_Reference - Get_Speed();
	U[k] = ((2*KP+KI*Ts)*E[k] + (KI*Ts-2*KP)*E[k-1] + 2*U[k-1])/2;
	if(U[k] < 0)
	{
		IN1.digitalWrite(LOW);
		IN2.digitalWrite(HIGH);
		if (U[k] < -100) U[k] = -100; //satura
		pwmMotor.PWMWrite(-U[k]);
	}
	else if(U[k] >= 0)
	{
		IN1.digitalWrite(HIGH);
		IN2.digitalWrite(LOW);
		if (U[k] > 100) U[k] = 100; //satura
		pwmMotor.PWMWrite(U[k]);
	}
	
	
	
	for (int i = 0; i < k; i++)
	{
		U[i] = U[i+1];
		E[i] = E[i+1];
	}

}

float Motor::Get_Speed()
{
	return encoder.getSpeed();	
}

float Motor::getSpeedRadS()
{
	return encoder.getSpeed()*rpmToRads;
}

float Motor::getU()
{
	return U[k];
}

float Motor::getE()
{
	return E[k];
}

float Motor::getTeta()
{
	return encoder.getTeta();	
}

float Motor::getDistance()
{
	return encoder.getTicks()*ticksToRad*r;
}

float Motor::getDeltaDistance()
{
	return encoder.getDeltaTicks()*ticksToRad*r;
}





