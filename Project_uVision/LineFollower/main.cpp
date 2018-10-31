//#include "stm32f10x.h" // comentar para tirar os arquivos que eu não fiz do programa

#include "Micro.h"
#include "SysClock.h"
#include "GPIO.h"
#include "TIMER.h"
//#include "PWM.h"
//#include "ADC.h"
//#include "ENCODER.h"

uint16_t ticks = 0;
bool direction = 0;

//TIM_REMAP Timer::TIM1Remap = NO_REMAP;

//Como gerar um erro ao tentar configurar o mesmo pino para duas funções?
//Como fazer uma função que configure só uma vez um remap para todos os canais do timer?
//qual o melhor modo de obter a leitura dos sensores, concersão única ou contínua?

//Aprender a usar atributos e funções estaticas

//bool GPIO::UsedPins[NUM_OF_IOs];

int main()
{
	SysClock Board;
	Board.SysClockInit();
	Board.SysTickInit(BASE_100ms);

	GPIO LED_placa(PC13, GP_OUTPUT_PUSH_PULL_2MHZ);
	//Encoder ENCTest(TIM3);
		
	while(1)
	{
		//ticks = ENCTest.GetEncTicks();
		//direction = ENCTest.GetEncDirection();

		if (Board.SysTickGetEvent()) LED_placa.tooglePin();
	}
	
}

void RCC_IRQHandler()
{
	
}

void RTCAlarm_IRQHandler()
{

}
