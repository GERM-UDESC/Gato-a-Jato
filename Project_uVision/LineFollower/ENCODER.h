#include "TIMER.h"

class Encoder : protected Timer
{
	private:
		void ConfigEncoder();
			
	public:
		Encoder(TIM_TypeDef *TIM);
		
		uint16_t GetEncTicks();
		bool GetEncDirection();
		
};

