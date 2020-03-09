#ifndef __F1012_H__
#define __F1012_H__


/********************************************************
 * Ĭ��ʹ��STM32(HAL��)��ʹ��DMA��ADC����ֵ���䣬
 * ��ֲ������ƽ̨ʱ��Ҫ�������к���
 *__attribute__((weak)) uint32_t F1012_GetAdcValue(void)
 */
//
//
#include "stm32h7xx_hal.h"
#define F1012_OS_USED     1 //stm32 �Ƿ�ʹ��ʵʱϵͳ
#define F1012_DMA_USED    1 //�Ƿ�ʹ��DMA


/********************************************************
 * ����Ӳ������趨һ�²���
 */
#define F1012_SAMPLE_RESISTOR_DIVIDED 1 //���з�ѹ������ʱ��ʹ��
#define F1012_SAMPLE_RESISTOR_R1 (2.0f) //K�� //��ѹ�������ű�
#define F1012_SAMPLE_RESISTOR_R2 (3.3f) //K�� //��ѹ�������ű�
#define F1012_SAMPLE_VOLTAGE_REF (3.3f) //�����ο���ѹ
#define F1012_SAMPLE_MAX         65535  //ADC�Ĳ�������
#define F1012_OVERSAMPLE_RATIO   1023   //ADC����������
/********************************************************
 * ���ݴ������
 *
 */
#define F1012_FILTER_LENGTH 10    //�˲������ݳ���
#define F1012_CALIBRATION_FACTORY_USED   1    //ʹ�ó���У׼�趨�������ʹ�ã���Ҫ��ǰУ׼
/********************************************************
 * �·��������������������ľ����ͺ��趨
 *
 */
#define F1012_ZERO_POINT_VOLTAGE         (1.0f)    //�������ѹ1V
#define F1012_ZERO_POINT_OFFSET          (0.04f)    //���Ʈ��40mV
#define F1012_OUTPUT_OFFSET              (0.1f)   //0.1V
#define F1012_FULL_POINT_FLOW            (20.0f)     //sccm
#define F1012_FULL_POINT_VOLTAGE         (5.0f)    //V

#define F1012_RESOLUTION_FACTORY         (F1012_FULL_POINT_FLOW/(F1012_FULL_POINT_VOLTAGE - F1012_ZERO_POINT_VOLTAGE))   //���ȣ�ÿV�Ƕ���sccm


uint32_t F1012_GetAdcValue(void);
float F1012_GetFlow(void);

#endif


