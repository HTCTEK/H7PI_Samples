#ifndef __AHT10_H__
#define __AHT10_H__

/********************************************************
 * STM32(HAL库)使用硬件I2C需要修改下列声明
 * 默认使用STM32进行读写，当需要移植到其他平台时重新声明下列函数
 * uint8_t aht10_Read(uint8_t* data, uint32_t length)
 * uint8_t aht10_Write(uint8_t* data,uint32_t length)
 * void aht10_delay(uint32_t ms)
 */
//
//include file
#include "stm32h7xx_hal.h"
#include "irq.h"

//define
#define AHT10_OS_USED 1            //stm32 是否使用实时系统
#define AHT10_I2C hi2c1            //stm32 I2C句柄
extern  I2C_HandleTypeDef hi2c1;

#if AHT10_OS_USED==1
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#endif

/*******************************************************
 *
 * AHT10寄存器和指令
 */
#define AHT10_ADDRESS       (0X38<<1)
#define AHT10_CMD_INIT      0XE1
#define AHT10_CMD_MEASURE   0XAC
#define AHT10_CMD_RESET     0XBA
#define AHT10_FILTER_LENGTH 1

int8_t  aht10_Init(void);
float   aht10_GetTemperature(void);
float   aht10_GetHumidity(void);
void    aht10_ReadData(void); //从传感器获取数据
void    aht10_Reset(void);
void    aht10_Trigger(void);
int8_t  aht10_IsCalEnable(void);
uint8_t aht10_GetStatus(void);

__attribute__((weak)) void aht10_delay(uint32_t ms);
__attribute__((weak)) uint8_t aht10_Read(uint8_t* data, uint32_t length);
__attribute__((weak)) uint8_t aht10_Write(uint8_t* data,uint32_t length);

#endif


