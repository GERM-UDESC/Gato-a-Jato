#include "MOTOR.h"

#define desired_iterations_delay 1000
uint16_t count_iterations = 0;


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
	
	
	this->motor_PWM = 0;
	this->desired_speed = 0;
};

  //configuração pinos Ponte H
  // HIGH HIGH            ---> "freio"
  // HIGH LOW or LOW HIGH ---> troca os sentidos
  // LOW LOW              ---> Para
  // STBY tem q ser HIGH para ligar a ponte H, se for LOW vai entrar em modo de stand by

void Motor::Set_Speed(int16_t Speed_Reference)
{
	if((Speed_Reference >= 0) && (Speed_Reference <=3000))
	{
		IN1.digitalWrite(HIGH);
		IN2.digitalWrite(LOW);
		desired_speed = Speed_Reference;
	}
	else if(Speed_Reference > (-3000))
	{
		IN1.digitalWrite(LOW);
		IN2.digitalWrite(HIGH);
		desired_speed = -Speed_Reference;
	}
};

void Motor::Handler()
{
	if(count_iterations >= desired_iterations_delay)
	{
		count_iterations = 0;
		if((desired_speed >= 0) && (desired_speed <=3000))
		{
			if	(Encoder_Motor.GetEncSpeed() > desired_speed)			(this->motor_PWM)--;
			else if	(Encoder_Motor.GetEncSpeed() < desired_speed)	(this->motor_PWM)++;
		}
		else if(desired_speed > (-3000))
		{
			if	(Encoder_Motor.GetEncSpeed() > desired_speed)			(this->motor_PWM)++;
			else if	(Encoder_Motor.GetEncSpeed() < desired_speed)	(this->motor_PWM)--;
		}
		if ((this->motor_PWM) > 65535) (this->motor_PWM) = 65535;
		else if ((this->motor_PWM) <= 0) (this->motor_PWM) = 0;
		PWM_Motor.PWMWrite((this->motor_PWM));
	}
	count_iterations++;
}

float Motor::Get_Speed()
{
	return Encoder_Motor.GetEncSpeed();	
}





