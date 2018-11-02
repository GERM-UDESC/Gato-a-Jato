#include "GPIO.h"
#include "TIMER.h"

class Encoder : protected Timer
{
	private:
		GPIO EncCH1;
		GPIO EncCH2;
		//Timer EncBaseTimer;			//Needed in case we need to read speed
		void ConfigEncoder();
			
	public:
		Encoder(TIM_TypeDef *TIM);
		
		uint16_t GetEncTicks();
		bool GetEncDirection();
		
};

