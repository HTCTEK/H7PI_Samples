#ifndef clockEnable_h
#define clockEnable_h

#include <stdint.h>

#include "stm32f30x.h"

#ifdef __cplusplus
extern "C"{
#endif
	
	typedef void (*ClkCmdFuncPtr) (uint32_t,FunctionalState);
	
#ifdef __cplusplus
}
#endif //cpp

#endif //all the file 

