#ifndef __BH1730_H__
#define __BH1730_H__


#include "stm32h7xx_hal.h"
#include "irq.h"
//
//define external
extern  I2C_HandleTypeDef hi2c2;
//
//define
#define BH1730_OS_USED 1                  //stm32 是否使用实时系统
#define BH1730_I2C     hi2c2                  //stm32 I2C句柄

#if BH1730_OS_USED==1
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#endif

#define BH1730_FILTER_LENGTH              10
#define BH1730_ADDRESS                    (0X29<<1)
#define BH1730_CMD                        0XE0
#define BH1730_CMD_INT_OUT_RESET          0X01
#define BH1730_CMD_STOP_MEASUREMENT_IN_MANUAL_INTEGRATION_MODE 0X02
#define BH1730_CMD_START_MEASUREMENT_IN_MANUAL_INTEGRATION_MODE 0X03
#define BH1730_CMD_RESET                  0X04

#define BH1730_REG                        0X80
#define BH1730_REG_CTRL                   0X00
#define BH1730_REG_TIMING                 0X01
#define BH1730_REG_INT                    0X02
#define BH1730_REG_TH_LOW_LSB             0X03
#define BH1730_REG_TH_LOW_MSB             0X04
#define BH1730_REG_TH_UP_LSB              0X05
#define BH1730_REG_TH_UP_MSB              0X06
#define BH1730_REG_GAIN                   0X07
#define BH1730_REG_ID                     0X12
#define BH1730_REG_DATA0_LSB              0X14
#define BH1730_REG_DATA0_MSB              0X15
#define BH1730_REG_DATA1_LSB              0X16
#define BH1730_REG_DATA1_MSB              0X17

#define BH1730_ADC_INTR_ACTIVE            0X20
#define BH1730_ADC_VALID                  0X10
#define BH1730_ONE_TIME                   0X08
#define BH1730_CONTINUOUS                 0X00
#define BH1730_DATA_SEL_TYPE0             0X04
#define BH1730_DATA_SEL_TYPE0_1           0X00
#define BH1730_ADC_ENABLE                 0X02
#define BH1730_ADC_DISABLE                0X00
#define BH1730_POWER_ON                   0X01
#define BH1730_POWER_OFF                  0X00

#define BH1730_INT_NOT_STOP               0X00
#define BH1730_INT_STOP_POWER_DOWN        0X40
#define BH1730_INT_ENABLE                 0X10
#define BH1730_INT_DISABLE                0X00
#define BH1730_INT_PERSIST_0              0 // Interrupt becomes active at each measurement end
#define BH1730_INT_PERSIST_1              0 // Interrupt status is updated at each measurement end.
#define BH1730_INT_PERSIST_2              0 // Interrupt status is updated if two consecutive threshold judgments are the same.
#define BH1730_INT_PERSIST_3              0 // When set 0011 or more, interrupt status is updated if same threshold judgments continue consecutively same times as the number set in “PERSIST”.


#define BH1730_GAIN_X1                    0
#define BH1730_GAIN_X2                    1
#define BH1730_GAIN_X64                   2
#define BH1730_GAIN_X128                  3

#define BH1730_DATA_TYPE                  BH1730_DATA_SEL_TYPE0_1

#define BH1730_TINT                       (2.8/1000) //2.8us
#define BH1730_ITIME                      0XDA
#define BH1730_ITIME_MS                   (BH1730_TINT*964*(256-BH1730_ITIME))
#define BH1730_TMT                        (BH1730_ITIME_MS+BH1730_TINT*714)

void bh1730_delay(uint32_t ms);
uint8_t bh1730_Read(uint8_t* data, uint32_t length);
uint8_t bh1730_Write(uint8_t* data,uint32_t length);

uint8_t bh1730_Init(void);
void    bh1730_ReadData(void);
float   bh1730_GetLux(void);


#endif

