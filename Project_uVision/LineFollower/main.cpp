//#include "stm32f10x.h" // comentar para tirar os arquivos que eu n�o fiz do programa

#include "Micro.h"
#include "GPIO.h"
#include "TIMER.h"
#include "PWM.h"
#include "SysClock.h"
#include "ADC.h"
#include "ENCODER.h"

uint16_t ticks;
bool direction;

TIM_REMAP Timer::TIM1Remap = NO_REMAP;

//Como gerar um erro ao tentar configurar o mesmo pino para duas fun��es?
//Como fazer uma fun��o que configure s� uma vez um remap para todos os canais do timer?
//qual o melhor modo de obter a leitura dos sensores, concers�o �nica ou cont�nua?

//Aprender a usar atributos e fun��es estaticas

int main()
{
	SysClock Board;
	Board.SysClockInit();
	Board.SysTickInit(BASE_100ms);

	GPIO LED_placa(GPIOC, PIN13, GP_OUTPUT_PUSH_PULL_2MHZ);
	Encoder ENCTest(TIM3);
		
	while(1)
	{
		ticks = ENCTest.GetEncTicks();
		direction = ENCTest.GetEncDirection();

		if (Board.SysTickGetEvent()) LED_placa.tooglePin();
	}
	
}

