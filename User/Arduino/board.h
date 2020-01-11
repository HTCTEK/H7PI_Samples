#ifndef __BOARD_H__
#define __BOARD_H__


#include "stdint.h"
#include "stm32h7xx_it.h"
#include "stm32h7xx_hal.h"
/****************************************************************
 * 
 * board setting
 * 
 * *************************************************************/
#define BOARD_GPIO_FREQ  GPIO_SPEED_FREQ_VERY_HIGH
#define BOARD_FPU        1
#define BOARD_OS         1

#if BOARD_OS==1
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************
 * 
 * pin define
 * 
 * *************************************************************/
enum
{
    D0=0,D1,D2,D3,D4,D5,D6,D7,
    D8,D9,D10,D11,D12,D13,D14,D15,
    D16,D17,D18,D19,D20,D21,D22,D23,
		D24,D25,D26,
    A0,A1,A2,A3,A4,A5,A6,A7,
};

/****************************************************************
 * 
 * pin info define
 * 
 * *************************************************************/
typedef struct 
{
    GPIO_TypeDef* gpio;
    uint16_t      pin;
}PinInfo_t;





extern const uint32_t  board_PinMode[];
extern const uint32_t  board_PinPull[];
extern const PinInfo_t board_PinMap[];


void setup(void);
void loop(void);
void board_GpioClockEnable(uint32_t pin);
void board_Init(void);


#ifdef __cplusplus
}
#endif


#endif
