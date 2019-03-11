////#include "stm32f10x.h" // comentar para tirar os arquivos que eu não fiz do programa
////#include "core_cm3.h"

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

////----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
////constantes para medidas de tempo
//uint32_t t_inicial = 10, t_final = 30, t_loop = 20;

////Constantes utilizadas para cálculos de erro
//float erro = 0, erro_anterior = 0, erro_P = 0, erro_I = 0, erro_D = 0, erro_total = 0;

////constantes
//#define KP 10 //20
//#define KI 0 //0.6
//#define KD 0 //1000

////velocidades
//#define V_Desejada 	25000
//#define V_max 			40000//65500
//#define V_min 			0

//int32_t Velocidade_Media = 0, Velocidade_E = 0, Velocidade_D = 0;

////Constantes usadas para a lógica da função de paradas
//uint32_t t_parada = 9 * 1000000;

////----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
////Não lembro se precisa definir as funções antes ou não, vou deixar comentado para garantir
//void calibra_sensores(Line_Sensor *Sensor_Board, uint32_t iteracoes); //Função para calibrar os sensores
//void leitura_sensores(Line_Sensor *Sensor_Board);                   //função para fazer a leitura dos sensores
//void calculo_erros_PID();                  //calcula os erros
//void seta_velocidade(PWM *PWM_E, PWM *PWM_D, GPIO *AIN1, GPIO *AIN2, GPIO *BIN1, GPIO *BIN2);                    //seta a velocidade
//void Blink_LED_Delay(SysClock *Board, GPIO *LED, Timer *Time_Generator, int t_delay);         //Função para piscar o LED usando delay
//void Parada(PWM *PWM_D, PWM *PWM_E, Timer *Time_Generator);                             //Função para definir quando o robô deverá parar

//int main1()
//{
//	//-----------------------------------Initiallize static parameters----------------------
//	Timer::Timer_Initiallize();
//	Encoder::Encoder_Initiallize();
//	
//	//----------------------------------------Setup----------------------------------------
//	SysClock Board;		//initiallize the board clock
//	
//	//Board LED
//	GPIO LED_Board(PC13, GP_OUTPUT_PUSH_PULL_2MHZ);
//	
//	//H bridge configuration
//	GPIO AIN2(PA10, GP_OUTPUT_PUSH_PULL_2MHZ);
//	GPIO AIN1(PA11, GP_OUTPUT_PUSH_PULL_2MHZ);
//	GPIO STBY(PA12, GP_OUTPUT_PUSH_PULL_2MHZ);
//	GPIO BIN1(PA15, GP_OUTPUT_PUSH_PULL_2MHZ);
//	GPIO BIN2(PB3, GP_OUTPUT_PUSH_PULL_2MHZ);
//	
//	//Timer
//	Timer Time_Generator(TIM2, COUNTER); //This one is dedicated to generate the time base in useconds
//	
//	//PWM configurations
//	PWM PWM_E(TIM3, TIM_CH2, PARTIAL_REMAP2);
//	PWM PWM_D(TIM3, TIM_CH1, PARTIAL_REMAP2);
//	
//	//Encoders configuration
//	Encoder ENC_E(TIM1);
//	Encoder ENC_D(TIM4);
//	
//	//Sensors
//	Line_Sensor Sensor_Board(ADC_CH0, ADC_CH1, ADC_CH2, ADC_CH3, ADC_CH4, ADC_CH5, ADC_CH6, ADC_CH7);
//	
//	//----------------------------------Initial Conditions------------------------------------------
//	AIN2.digitalWrite(HIGH);
//	AIN1.digitalWrite(LOW);
//	STBY.digitalWrite(HIGH);
//	BIN1.digitalWrite(HIGH);
//	BIN2.digitalWrite(LOW);
//	
//	PWM_D.PWMWrite(0);
//	PWM_E.PWMWrite(0);
//	
//	//-----------------------------------------------------------------------------------------------	
//	LED_Board.digitalWrite(LOW);		//Ligado -> LOW --- Desligado -> HIGH
//  calibra_sensores(&Sensor_Board, 500000);
//  Blink_LED_Delay(&Board, &LED_Board, &Time_Generator, 4);
//	t_parada += Time_Generator.GetTime_usec();
//  
//	//loop
//	while(1)
//	{
//		t_inicial = Time_Generator.GetTime_usec();
//		leitura_sensores(&Sensor_Board);
//		calculo_erros_PID();
//		seta_velocidade(&PWM_E, &PWM_D, &AIN1, &AIN2, &BIN1, &BIN2);
//		//Parada(PWM_D, PWM_E, Time_Generator);
//		t_final = Time_Generator.GetTime_usec();
//		t_loop = t_final - t_inicial; 	//lembrando que o valor está em micro segundos
//	}
//}

////----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
////função para fazer a leitura dos sensores e calcular o erro
//void leitura_sensores(Line_Sensor *Sensor_Board)
//{
//  erro_anterior = erro;
//  erro = Sensor_Board->Read_Sensor();
//}

////----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
////calcula os erros e o PID
//void calculo_erros_PID()
//{
//  erro_P = erro;
//  //erro_I = erro_I + ((erro + erro_anterior) / 2) * t_loop;
//  //erro_D = ((erro - erro_anterior) * 1000) / (t_loop);
//  erro_total = KP * erro_P + KI * erro_I + KD * erro_D;
//}
////----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
////seta a velocidade
//void seta_velocidade(PWM *PWM_E, PWM *PWM_D, GPIO *AIN1, GPIO *AIN2, GPIO *BIN1, GPIO *BIN2)
//{
//  if (Velocidade_Media < V_Desejada)
//  {
//    Velocidade_Media += 50;
//  }
//  else
//  {
//    Velocidade_Media = V_Desejada;
//  }

//  Velocidade_E = Velocidade_Media + erro_total;
//  Velocidade_D = Velocidade_Media - erro_total;

//  if (Velocidade_E <= 0)                          //Inverte a rotação do motor para reduzir a velocidade mais rápido
//  {
//    Velocidade_E = -Velocidade_E;
//		BIN1->digitalWrite(LOW);
//		BIN2->digitalWrite(HIGH);
//  }
//  else
//  {
//    BIN1->digitalWrite(HIGH);
//		BIN2->digitalWrite(LOW);
//  }

//  if (Velocidade_D <= 0)                        //Inverte a rotação do motor para reduzir a velocidade mais rápido
//  {
//    Velocidade_D = -Velocidade_D;
//    AIN1->digitalWrite(HIGH);
//		AIN2->digitalWrite(LOW);
//  }
//  else
//  {
//    AIN1->digitalWrite(LOW);
//		AIN2->digitalWrite(HIGH);
//  }

//  if (Velocidade_E >= V_max)
//  {
//    Velocidade_E = V_max;
//    //    erro_I = erro_I - ((erro + erro_anterior) / 2) * t_loop;  //anti windup
//  }
//  if (Velocidade_D >= V_max)
//  {
//    Velocidade_D = V_max;
//    //    erro_I = erro_I - ((erro + erro_anterior) / 2) * t_loop;  //anti windup
//  }

//	PWM_D->PWMWrite(Velocidade_D);
//	PWM_E->PWMWrite(Velocidade_E);
//}

////----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//void Parada(PWM *PWM_D, PWM *PWM_E, Timer *Time_Generator)
//{
//  //Parada por tempo
//  if (Time_Generator->GetTime_usec() > t_parada)    //Desliga os motores se já tiver passado o tempo 
//  {
//	PWM_D->PWMWrite(0);
//	PWM_E->PWMWrite(0);
//    while (1 > 0);                      //Fica nessa parte infinitamente
//  }
//}

////----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//void calibra_sensores(Line_Sensor *Sensor_Board, uint32_t iteracoes)
//{
//	for (uint32_t i = 0; i < iteracoes; i++)
//	{
//		Sensor_Board->Calibrate_Sensor();
//	}
//}

////----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
////Função para piscar o LED
//void Blink_LED_Delay(SysClock *Board, GPIO *LED, Timer *Time_Generator, int t_delay)
//{
//	uint32_t initial_time = Time_Generator->GetTime_usec();
//	uint16_t blink_counter = 0;
//	
//	while (blink_counter < 10*t_delay)
//	{
//		if (Board->SysTickGetEvent()) 
//		{
//			LED->tooglePin();
//			blink_counter++;
//		}  
//	}
//}


