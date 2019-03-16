#include "MOTOR.h"

int16_t Motor::Speed_Reference[Number_of_Motor];
float	Motor::E[Number_of_Motor][desired_size];				//Error
bool Motor::handlerStatus[Number_of_Motor];	
Motor *Motor::Ptr[Number_of_Motor];

void Motor::Motor_Initialiize()
{
	for (uint8_t i = 0; i < Number_of_Motor; i++)
	{
		Speed_Reference[i] = 0;
		handlerStatus[i] = 0;
		for (uint8_t j = 0; j < desired_size; j++)
		{
			E[i][j] = 0;				//Error
		}	
	}	
}

void Motor::Motor_Handler_by_time()
{
	for (uint8_t i = 0; i < Number_of_Motor; i++)
	{
		E[i][k] = Speed_Reference[i] - Encoder::Speed[i];
		handlerStatus[i] = 1;
	}		
	Motor::Ptr[Motor_1]->Handler();
	Motor::Ptr[Motor_4]->Handler();
}

Motor::Motor(TIM_TypeDef *TIM_PWM, TIM_CHANNELS channel_PWM, TIM_REMAP TIM_PWMremap, TIM_TypeDef *TIM_ENCODER, GPIO_IO_ENUM IO_Pin_IN1, GPIO_IO_ENUM IO_Pin_IN2)
{
	//Configure the timer for the PWM
	PWM_Motor.SetTim(TIM_PWM);
	PWM_Motor.SetTIMChannel(channel_PWM);
	PWM_Motor.SetTIMMode(PWM_MODE);
	PWM_Motor.TimerInit();
	PWM_Motor.SetTIMRemap(TIM_PWMremap);
	PWM_Motor.ConfigPWMPin();
	PWM_Motor.PWMInit();
	PWM_Motor.PWMWrite(0);   //Turn off the motor
	
	//Configure the timer for the encoder/
	Encoder_Motor.SetTim(TIM_ENCODER);
	Encoder_Motor.ConfigEncoder();
	
	//Configure the IN1 and IN2
	IN1.SetIOPin(IO_Pin_IN1);
	IN1.SetGPIOPortPin(IO_Pin_IN1);
	IN1.SetGPIOMode(GP_OUTPUT_PUSH_PULL_50MHZ);
	IN1.ConfigGPIOPin();
	IN1.Config_PU_PD(PULL_DOWN);		//Config PULL_DOWN as default
	
	IN2.SetIOPin(IO_Pin_IN2);
	IN2.SetGPIOPortPin(IO_Pin_IN2);
	IN2.SetGPIOMode(GP_OUTPUT_PUSH_PULL_50MHZ);
	IN2.ConfigGPIOPin();
	IN2.Config_PU_PD(PULL_DOWN);		//Config PULL_DOWN as default
	
	IN1.digitalWrite(LOW);
	IN2.digitalWrite(LOW);
	
	if (Encoder_Motor.GetTim() == TIM1) 
	{
		Motor_number = Motor_1;
		Motor::Ptr[Motor_number] = this;
		
	}
	else if (Encoder_Motor.GetTim() == TIM2)
	{
		Motor_number = Motor_1;
	}
	else if (Encoder_Motor.GetTim() == TIM3) 
	{
		Motor_number = Motor_3;
	}
	else if (Encoder_Motor.GetTim() == TIM4) 
	{
		Motor_number = Motor_4;
	}
	
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
	Motor::Speed_Reference[Motor_number] = Speed_Reference;
};

void Motor::Handler()
{
	if (handlerStatus[Motor_number] == 1)
	{		
		U[k] = ((2*KP+KI*Ts)*E[Motor_number][k] + (KI*Ts-2*KP)*E[Motor_number][k-1] + 2*U[k-1])/2;
	//	U[k] = (2*KP +KI*Ts)*E[Motor_number][k]+(KI*Ts - 2*KP)*E[Motor_number][k-1]+U[k-2];
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
		
		PWM_Motor.PWMWrite(U[k]);
		
		for (int i = 0; i < k; i++)
		{
			U[i] = U[i+1];
			E[Motor_number][i] = E[Motor_number][i+1];
		}
		
		handlerStatus[Motor_number] = 0;
	}
}

float Motor::Get_Speed()
{
	return Encoder_Motor.GetEncSpeed();	
}





