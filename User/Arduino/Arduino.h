#ifndef Arduino_h
#define Arduino_h

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "binary.h"
#include "wiring.h"
#include "wiring_constants.h"
#include "wiring_digital.h"
#include "wiring_analog.h"

#include "board.h"

#ifdef __cplusplus
extern "C"{
#endif
	
	void init();
	void setup();
	void loop();
	extern void serialEventRun() __attribute__((weak));
	
	extern uint32_t SystemCoreClock;
	
	#define clockCyclePerMillis()				(SystemCoreClock/1000L)
	#define clockCyclePerMicrosecond			(SystemCoreClock/1000000L)
	
	#define digitalPinToPort(P)					(pinMap[P].GPIOx)
	#define digitalPinToBitMask(P)				(pinMap[p].GPIO_Pin)
	
#ifdef __cplusplus
}
/********************************************************************************
* 
* user porting
*
********************************************************************************/
#include "board.h"

#endif //end of cpp
	
#endif //all the file 
