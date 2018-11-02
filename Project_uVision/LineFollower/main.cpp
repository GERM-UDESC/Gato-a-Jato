//#include "stm32f10x.h" // comentar para tirar os arquivos que eu não fiz do programa
//#include "core_cm3.h"

#include "Micro.h"
#include "SysClock.h"
#include "GPIO.h"
#include "TIMER.h"
#include "PWM.h"
#include "ADC.h"
#include "ENCODER.h"

uint16_t Ticks = 0;
uint16_t lastTicks = 0;
bool direction = 0;
uint16_t timecounter = 0;
uint16_t motorSpeed = 0;

//Como gerar um erro ao tentar configurar o mesmo pino para duas funções?
//Como fazer uma função que configure só uma vez um remap para todos os canais do timer?
//qual o melhor modo de obter a leitura dos sensores, concersão única ou contínua?

//Problema com inicialização de variáveis

//Aprender a usar atributos e funções estaticas

//bool GPIO::UsedPins[NUM_OF_IOs];

int main()
{
	SysClock Board;
	Board.SysTickInit(BASE_100ms);

	GPIO LED_placa(PC13, GP_OUTPUT_PUSH_PULL_2MHZ);
	Timer InterruptGenerator(TIM1, COUNTER);
	PWM Motortest(TIM2, TIM_CH1, NO_REMAP);
	Encoder ENCTest(TIM3);
	Motortest.PWMWrite(25000);
		
	while(1)
	{
		Ticks = ENCTest.GetEncTicks();
		direction = ENCTest.GetEncDirection();
			

		if (Board.SysTickGetEvent()) LED_placa.tooglePin();
	}
	
}

extern "C" {
		void TIM1_UP_IRQHandler()
	{
		TIM1->SR &= ~(1<<0);
		timecounter = timecounter + 1;
		motorSpeed = Ticks - lastTicks;
		lastTicks = Ticks;
	}
}
