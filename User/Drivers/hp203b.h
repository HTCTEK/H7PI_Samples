#ifndef __HP203B_H__
#define __HP203B_H__


#include "stm32h7xx_hal.h"
#include "irq.h"
//
//define external
extern  I2C_HandleTypeDef hi2c2;
//
//define
#define HP203B_OS_USED 1                  //stm32 是否使用实时系统
#define HP203B_I2C hi2c2                  //stm32 I2C句柄

#if HP203B_OS_USED==1
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#endif


#define HP203B_CSB1_ADDRESS     (0XEC)
#define HP203B_CSB0_ADDRESS     (0XEE)
#define HP203B_ADDRESS          HP203B_CSB0_ADDRESS
#define HP203B_RESET            0X06
#define HP203B_READ_PT          0X10
#define HP203B_READ_AT          0X00
#define HP203B_READ_P           0X30
#define HP203B_READ_A           0X31
#define HP203B_READ_T           0X32
#define HP203B_ANA_CAL          0X28
#define HP203B_READ_REG(ADDR)  (0X80|ADDR)
#define HP203B_WRITE_REG(ADDR) (0XC0|ADDR)


#define HP203B_CVT        (0X2<<5)
#define HP203B_CHANNEL_PT 0X00
#define HP203B_CHANNEL_T  0X02
#define HP203B_OSR_4096   (0X00<<2)
#define HP203B_OSR_2048   (0X01<<2)
#define HP203B_OSR_1024   (0X02<<2)
#define HP203B_OSR_512   (0X03<<2)
#define HP203B_OSR_256   (0X04<<2)
#define HP203B_OSR_128   (0X05<<2)
#define HP203B_FILTER_LENGTH 10

__attribute__((weak)) void hp203b_delay(uint32_t ms);
__attribute__((weak)) uint8_t hp203b_Read(uint8_t* data, uint32_t length);
__attribute__((weak)) uint8_t hp203b_Write(uint8_t* data,uint32_t length);

uint8_t hp203b_Init(void);
void hp203b_ReadData(void);
float hp203b_GetPressure(void);
float hp203b_GetTemperature(void);
float hp203b_GetAltitude(void);



#endif
