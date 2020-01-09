#ifndef __AWM3150V_H__
#define __AWM3150V_H__

/********************************************************
 * 默认使用STM32(HAL库)，使用DMA对ADC采样值传输，
 * 移植到其他平台时需要声明下列函数
 *__attribute__((weak)) uint32_t awm_GetAdcValue(void)
 */
//
//
#include "stm32h7xx_hal.h"
#define AWM_OS_USED     0 //stm32 是否使用实时系统
#define AWM_DMA_USED    1 //是否使用DMA


/********************************************************
 * 根据硬件设计设定一下参数
 */
#define AWM_SAMPLE_RESISTOR_DIVIDED 1 //当有分压采样的时候使用
#define AWM_SAMPLE_RESISTOR_R1 (2.0f) //KΩ //分压电阻上桥臂
#define AWM_SAMPLE_RESISTOR_R2 (3.0f) //KΩ //分压电阻下桥臂
#define AWM_SAMPLE_VOLTAGE_REF (3.3f) //采样参考电压
#define AWM_SAMPLE_MAX         65535  //ADC的采样精度
#define AWM_OVERSAMPLE_RATIO   1024
/********************************************************
 * 数据处理参数
 *
 */
#define AWM_FILTER_LENGTH 10    //滤波器数据长度
#define AWM_CALIBRATION_FACTORY_USED   1    //使用出厂校准设定，如果不使用，需要提前校准
/********************************************************
 * 下方参数根据流量传感器的具体型号设定
 *
 */
#define AWM_ZERO_POINT_VOLTAGE         (1.0f)    //输出零点电压1V
#define AWM_ZERO_POINT_OFFSET          (0.1f)    //零点飘移100mV
#define AWM_OUTPUT_OFFSET              (0.05f)   //5%
#define AWM_CALIBRATION_POINT_FLOW     (25.0f)     //sccm
#define AWM_CALIBRATION_POINT_VOLTAGE  (3.4f)    //V
#define AWM_RESOLUTION_FACTORY         (AWM_CALIBRATION_POINT_FLOW/(AWM_CALIBRATION_POINT_VOLTAGE - AWM_ZERO_POINT_VOLTAGE))   //精度，每V是多少sccm


uint32_t awm_GetAdcValue(void);
float awm_GetFlow(void);


#endif

