#include "TIMER.h"

class Encoder : protected Timer
{
	private:
		GPIO EncCH1;
		GPIO EncCH2;
		void ConfigEncoder();
			
	public:
		Encoder(TIM_TypeDef *TIM);
		
		uint16_t GetEncTicks();
		bool GetEncDirection();
		
};

