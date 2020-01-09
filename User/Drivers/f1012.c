#include "f1012.h"

#if (F1012_CALIBRATION_FACTORY_USED == 0)

float F1012_RESOLUTION_USER = 0.0;

#endif
/*
 *
 * 获取一个ADC值
 *
 */
__attribute__((weak)) uint32_t F1012_GetAdcValue(void)
{
#if (F1012_DMA_USED==0)

	return 0;
#elif (F1012_DMA_USED==1)

	return 0;
#endif
}
/*
 *
 * 最大最小值去除并求平均
 *
 */
float F1012_Filter(uint32_t* data)
{
	uint32_t sum = 0;
	float    avg = 0.0;

	for(int i = 0; i < F1012_FILTER_LENGTH; i++)
	{
		sum += data[i];
	}
	avg = ((float)sum)/(F1012_FILTER_LENGTH);
	//
	//移动一位
	//
	for(int i = F1012_FILTER_LENGTH-1; i > 0; i--)
	{
		data[i] = data[i-1];
	}
	avg = avg/(F1012_SAMPLE_MAX*F1012_OVERSAMPLE_RATIO)*F1012_SAMPLE_VOLTAGE_REF;
	return avg;
}
/*
 *
 * 获取流量值
 *
 */

	static uint32_t flowSampleValue[F1012_FILTER_LENGTH] = {0};

float F1012_GetFlow(void)
{
	double flowValue = 0.0;
	flowSampleValue[0] = F1012_GetAdcValue(); 
	flowValue = F1012_Filter((uint32_t*)flowSampleValue);

#if (F1012_SAMPLE_RESISTOR_DIVIDED==1)
	flowValue = flowValue*(F1012_SAMPLE_RESISTOR_R1+F1012_SAMPLE_RESISTOR_R2)/F1012_SAMPLE_RESISTOR_R2;
#endif

#if (F1012_CALIBRATION_FACTORY_USED==1)
	flowValue = (flowValue-F1012_ZERO_POINT_VOLTAGE)*F1012_RESOLUTION_FACTORY;
#else
	flowValue *= F1012_RESOLUTION_USER;
#endif

	flowValue = flowValue < 0 ? 0 : flowValue; 
	return flowValue;
}

