/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file wirish_time.h
 * @brief Timing and delay functions.
 */

#ifndef __WIRISH_TIME_H_
#define __WIRISH_TIME_H_

#ifdef __cplusplus
extern "C"{
#endif
#include "Board.h"

#define US_PER_MS               1000

/**
 * Returns time (in milliseconds) since the beginning of program
 * execution. On overflow, restarts at 0.
 * @see micros()
 */
static inline uint32_t millis(void) {
    return uwTick;
}

/**
 * Returns time (in microseconds) since the beginning of program
 * execution.  On overflow, restarts at 0.
 * @see millis()
 */
static inline uint32_t micros(void) {
	uint32_t ticks ;
  uint32_t count ;
 
	//SysTick->CTRL;
	do {
		 ticks = SysTick->VAL;
		 count = uwTick;
	} while (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk);

	return count * 1000 + (SysTick->LOAD + 1 - ticks) / (SystemCoreClock/1000000) ;
}

/**
 * Delay for at least the given number of milliseconds.
 *
 * Interrupts, etc. may cause the actual number of milliseconds to
 * exceed ms.  However, this function will return no less than ms
 * milliseconds from the time it is called.
 *
 * @param ms the number of milliseconds to delay.
 * @see delayMicroseconds()
 */
void delay(unsigned long ms);

/**
 * Delay for at least the given number of microseconds.
 *
 * Interrupts, etc. may cause the actual number of microseconds to
 * exceed us.  However, this function will return no less than us
 * microseconds from the time it is called.
 *
 * @param us the number of microseconds to delay.
 * @see delay()
 */
void delayMicroseconds(uint32_t us);

#ifdef __cplusplus
}
#endif

#endif
