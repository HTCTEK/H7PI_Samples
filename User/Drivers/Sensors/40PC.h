#ifndef __PRESS3150V_H__
#define __PRESS3150V_H__

/********************************************************
 * 默认使用STM32(HAL库)，使用DMA对ADC采样值传输，
 * 移植到其他平台时需要声明下列函数
 *__attribute__((weak)) uint32_t PRESS_GetAdcValue(void)
 */
//
//
#include "stm32h7xx_hal.h"
#define PRESS_OS_USED     0 //stm32 是否使用实时系统
#define PRESS_DMA_USED    1 //是否使用DMA


/********************************************************
 * 根据硬件设计设定一下参数
 */
#define PRESS_SAMPLE_RESISTOR_DIVIDED 1 //当有分压采样的时候使用
#define PRESS_SAMPLE_RESISTOR_R1 (2.0f) //KΩ //分压电阻上桥臂
#define PRESS_SAMPLE_RESISTOR_R2 (3.3f) //KΩ //分压电阻下桥臂
#define PRESS_SAMPLE_VOLTAGE_REF (3.3f)//采样参考电压
#define PRESS_SAMPLE_MAX         65535  //ADC的采样精度
#define PRESS_OVERSAMPLE_RATIO   1024



/********************************************************
 * 数据处理参数
 *
 */
#define PRESS_FILTER_LENGTH 10    //滤波器数据长度
#define PRESS_CALIBRATION_FACTORY_USED   1    //使用出厂校准设定，如果不使用，需要提前校准



/********************************************************
 * 下方参数根据流量传感器的具体型号设定
 *40PC015G2A 
 * 0~15PSIG,4V（0.5~4.5V）
 */
#define PRESS_ZERO_POINT_OFFSET          (0.5f)    //零点飘移0.5V
#define PRESS_SENSITIVITY                (0.2667f) //0.2667V/PSI



double    pressure_GetPressure(void);
uint32_t pressure_GetAdcValue(void);
#endif

