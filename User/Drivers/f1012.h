#ifndef __F1012_H__
#define __F1012_H__


/********************************************************
 * 默认使用STM32(HAL库)，使用DMA对ADC采样值传输，
 * 移植到其他平台时需要声明下列函数
 *__attribute__((weak)) uint32_t F1012_GetAdcValue(void)
 */
//
//
#include "stm32h7xx_hal.h"
#define F1012_OS_USED     1 //stm32 是否使用实时系统
#define F1012_DMA_USED    1 //是否使用DMA


/********************************************************
 * 根据硬件设计设定一下参数
 */
#define F1012_SAMPLE_RESISTOR_DIVIDED 1 //当有分压采样的时候使用
#define F1012_SAMPLE_RESISTOR_R1 (2.0f) //KΩ //分压电阻上桥臂
#define F1012_SAMPLE_RESISTOR_R2 (3.3f) //KΩ //分压电阻下桥臂
#define F1012_SAMPLE_VOLTAGE_REF (3.3f) //采样参考电压
#define F1012_SAMPLE_MAX         65535  //ADC的采样精度
#define F1012_OVERSAMPLE_RATIO   1023   //ADC过采样倍数
/********************************************************
 * 数据处理参数
 *
 */
#define F1012_FILTER_LENGTH 10    //滤波器数据长度
#define F1012_CALIBRATION_FACTORY_USED   1    //使用出厂校准设定，如果不使用，需要提前校准
/********************************************************
 * 下方参数根据流量传感器的具体型号设定
 *
 */
#define F1012_ZERO_POINT_VOLTAGE         (1.0f)    //输出零点电压1V
#define F1012_ZERO_POINT_OFFSET          (0.04f)    //零点飘移40mV
#define F1012_OUTPUT_OFFSET              (0.1f)   //0.1V
#define F1012_FULL_POINT_FLOW            (20.0f)     //sccm
#define F1012_FULL_POINT_VOLTAGE         (5.0f)    //V

#define F1012_RESOLUTION_FACTORY         (F1012_FULL_POINT_FLOW/(F1012_FULL_POINT_VOLTAGE - F1012_ZERO_POINT_VOLTAGE))   //精度，每V是多少sccm


uint32_t F1012_GetAdcValue(void);
float F1012_GetFlow(void);

#endif


