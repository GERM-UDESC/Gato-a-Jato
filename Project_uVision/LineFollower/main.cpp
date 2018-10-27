//#include "stm32f10x.h" // comentar para tirar os arquivos que eu não fiz do programa

#include "Micro.h"
#include "GPIO.h"
#include "TIMER.h"
#include "PWM.h"
#include "SysClock.h"
#include "ADC.h"

uint16_t adc_convertion;

//Como gerar um erro ao tentar configurar o mesmo pino para duas funções?
//Como fazer uma função que configure só uma vez um remap para todos os canais do timer?
//qual o melhor modo de obter a leitura dos sensores, concersão única ou contínua?

//Aprender a usar atributos e funções estaticas

int main()
{
	SysClock Board;
	Board.SysClockInit();
	Board.SysTickInit(BASE_100ms);

	GPIO LED_placa(GPIOC, PIN13, GP_OUTPUT_PUSH_PULL_2MHZ);
	ADC ADC_PB1(ADC_CH9);
	
	PWM LED_Verde(TIM1, TIM_CH1, NO_REMAP);
	PWM LED_Branco(TIM1, TIM_CH2, NO_REMAP);
	PWM LED_Amarelo(TIM1, TIM_CH3, NO_REMAP);
	PWM LED_Vermelho(TIM1, TIM_CH4, NO_REMAP);
		
	while(1)
	{
		adc_convertion = 16*(ADC_PB1.analogRead());			//save the value of the convertion
		if (adc_convertion > 65300) adc_convertion = 65300;
		else if (adc_convertion <= 0) adc_convertion = 0;
		LED_Verde.PWMWrite(adc_convertion);
		LED_Amarelo.PWMWrite(adc_convertion);
		LED_Branco.PWMWrite(adc_convertion);
		LED_Vermelho.PWMWrite(adc_convertion);

		if (Board.SysTickGetEvent()) LED_placa.tooglePin();
	}
}

