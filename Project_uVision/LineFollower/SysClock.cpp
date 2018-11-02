#include "SysClock.h"

/*
This function will set as default the HSE as clock Source, making it pass through the PLL and be multiplied by 9 to get the 72MHz
HSE = High Speed External Clock 
As in this board we have the External Crystal, which is much more acurated than the internal clock, and we are not aimming to a low power
application, there is no reason to avoid using the External Crystal

It will also configure the external 32.764kHz oscilator as the RTC source

This function will also configure the clock off all periferals and buses as the maximus allowed

*/
SysClock::SysClock()
{
	SysClockInit();
}

void SysClock::SysClockInit()
{
	//1. Fisrt enable the required clock and wait until the clock is Ready
	
	RCC->CR |= (1<<16);						//Turn on HSE clock
	
	while(!(RCC->CR & (1<<17)));	//Wait until its Ready
	
	//2. Configure the PLL and enable it
	
	RCC->CFGR |= ((1<<20) | (1<<19) | (1<<18)); //Set the PLL multiplication factor
	
	RCC->CFGR |= (1<<16);	//Select the HSE as clock source instead off HSI in the PLL	
	
	RCC->CR |= (1<<24);		//Enable de PLL
	
	while(!(RCC->CR & (1<<25)));	//Wait until the PLL clock is stable
	
	//3. Initialises the busses clock prescalers according to the application requiriments and maximum limits
	
	//APB1 bus must not exced 36MHz
	RCC->CFGR |= (1<<10);	//APB1 prescalers 2
	
	//ADCs clock must not exced 14MHz???, as the input clock to this peripheral is 72MHz, it must be divided by 6
	RCC->CFGR |= (1<<15);
	
	//4. Configure the Flash latency properly by referring to MCU RM
	
	FLASH->ACR |= (1<<1);	//Put 2 wait states into the read/write operations with the flash memory
	
	//5. Select newly enabled Clock as SYSCLK

	RCC->CFGR |= (1<<1);	//Changes from HSI to PLL
	
	RCC->CR &= ~(1<<0);		//Turn off HSI to save power
	
	/*************************************************************************************************************/
//	//Low Speed Clock configuration
//	
//	/*
//		After reset, access to the Backup registers and RTC is disabled and the Backup domain
//		(BKP) is protected against possible parasitic write access. To enable access to the Backup
//		registers and the RTC, proceed as follows:
//	*/
//	//enable the power and backup interface clocks by setting the PWREN and BKPEN bits in the RCC_APB1ENR register
//	RCC->APB1ENR |= (1<<27) | (1<<28);
//	
//	//set the DBP bit the Power Control Register (PWR_CR) to enable access to the Backup registers and RTC.
//	PWR->CR |= (1<<8);
//	
//	
//	//Now the RTC Clock initialization
//	//1. Turn on LSE
//	RCC->BDCR |= (1<<0);
//	
//	//2. Wait until the LSE is stable
//	while(!(RCC->BDCR & (1<<1)));	//Wait until the PLL clock is stable
//	
//	//3. Select LSE as RTC Clock source
//	RCC->BDCR |= (1<<8);
//	
//	//4. Reset the backup Domain
//	RCC->BDCR |= (1<<16);		//this is actually not needed, but just to be sure
//	
//	//5. Enable the RTC clock
//	RCC->BDCR |= (1<<15);
//	
//	/*****************************************************************************/
//	//Start the RTC configuration
//	//After every configuration, it's needed to wait the last operation to be finished before doing another one
//	//1. Enter in configuration mode
//	while(!(RTC->CRL & (1<<5)));	//Wait until the Last write operation on RTC registers is finished (this one is just to be sure)
//	RTC->CRL |= (1<<4);
//	while(!(RTC->CRL & (1<<5)));	//Wait until the Last write operation on RTC registers is finished
//	
//	//2.
//	
};

void SysClock::MCO()
{
	GPIO OutClock(PA8, AF_OUTPUT_PUSH_PULL_50MHZ);	//just to test the board clock
	RCC->CFGR |= ((1<<26) | (1<<24) | (1<<25));			//

}

void SysClock::SysTickInit(SysTickBaseTimeEnum BASE_TIME)
{
	SysTick->LOAD = BASE_TIME; 
	SysTick->CTRL = 5;
}


bool SysClock::SysTickGetEvent()
{
	return SysTick->CTRL & (1<<16);
}


