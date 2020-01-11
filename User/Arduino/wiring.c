#include <stdint.h>

#include "board.h"
#include "wiring.h"

uint32_t millis( void )
{
	return uwTick;
}

// Interrupt-compatible version of micros
// Theory: repeatedly take readings of SysTick counter, millis counter and SysTick interrupt pending flag.
// When it appears that millis counter and pending is stable and SysTick hasn't rolled over, use these 
// values to calculate micros. If there is a pending SysTick, add one to the millis counter in the calculation.

uint32_t micros( void )
{
	uint32_t ticks ;
  uint32_t count ;
 
	SysTick->CTRL;
	do {
		 ticks = SysTick->VAL;
		 count = uwTick;
	} while (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk);

	return count * 1000 + (SysTick->LOAD + 1 - ticks) / (SystemCoreClock/1000000) ;
}

void yield(void){ } //do nothing!

void delay( uint32_t ms )
{
	#if (BOARD_OS==0)
    uint32_t end = uwTick + ms;
    while (uwTick < end)
    	yield();
	#else
		osDelay(ms);
	#endif
}

