#include "awm3150v.h"

#if (AWM_CALIBRATION_FACTORY_USED == 0)

float AWM_RESOLUTION_USER = 0.0;

#endif
/*
 *
 * 获取一个ADC值
 *
 */
__attribute__((weak)) uint32_t awm_GetAdcValue(void)
{
#if (AWM_DMA_USED==0)

	return 0;
#elif (AWM_DMA_USED==1)

	return 0;
#endif
}
/*
 *
 * 最大最小值去除并求平均
 *
 */
float awm_Filter(uint32_t* data)
{
	uint32_t sum = 0;
	float    avg = 0.0;

	for(int i = 0; i < AWM_FILTER_LENGTH; i++)
	{
		sum += data[i];
	}
	avg = ((float)sum)/(AWM_FILTER_LENGTH);
	//
	//移动一位
	//
	for(int i = AWM_FILTER_LENGTH-1; i > 0; i--)
	{
		data[i] = data[i-1];
	}
	avg = avg/(AWM_SAMPLE_MAX*AWM_OVERSAMPLE_RATIO)*AWM_SAMPLE_VOLTAGE_REF;
	return avg;
}
/*
 *
 * 获取流量值
 *
 */

	static uint32_t flowSampleValue[AWM_FILTER_LENGTH] = {0};

float awm_GetFlow(void)
{
	double flowValue = 0.0;
	flowSampleValue[0] = awm_GetAdcValue(); 
	flowValue = awm_Filter((uint32_t*)flowSampleValue);

#if (AWM_SAMPLE_RESISTOR_DIVIDED==1)
	flowValue = flowValue*(AWM_SAMPLE_RESISTOR_R1+AWM_SAMPLE_RESISTOR_R2)/AWM_SAMPLE_RESISTOR_R2;
#endif

#if (AWM_CALIBRATION_FACTORY_USED==1)
	flowValue = (flowValue-AWM_ZERO_POINT_VOLTAGE)*AWM_RESOLUTION_FACTORY;
#else
	flowValue *= AWM_RESOLUTION_USER;
#endif

	flowValue = flowValue < 0 ? 0 : flowValue; 
	return flowValue;
}

