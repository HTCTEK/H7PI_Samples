#include "40PC.h"

#if (PRESS_CALIBRATION_FACTORY_USED == 0)

float PRESS_RESOLUTION_USER = 0.0;

#endif
/*
 *
 * 获取一个ADC值
 *
 */
__attribute__((weak)) uint32_t pressure_GetAdcValue(void)
{
#if (PRESS_DMA_USED==0)

	return 0;
#elif (PRESS_DMA_USED==1)

	return 0;
#endif
}
/*
 *
 * 最大最小值去除并求平均
 *
 */
double pressure_Filter(uint32_t* data)
{
	uint64_t   sum = 0;
	double    avg = 0.0f;

	for(int i = 0; i < PRESS_FILTER_LENGTH; i++)
	{
		sum += data[i];
	}
	avg = ((double)sum)/(PRESS_FILTER_LENGTH);
	//
	//移动一位
	//
	for(int i = PRESS_FILTER_LENGTH-1; i > 0; i--)
	{
		data[i] = data[i-1];
	}
	avg = avg/(PRESS_SAMPLE_MAX*PRESS_OVERSAMPLE_RATIO)*PRESS_SAMPLE_VOLTAGE_REF;
	return avg;
}
/*
 *
 * 获取压力值
 *
 */
	
	static uint32_t PressureSampleValue[PRESS_FILTER_LENGTH] = {0};
double pressure_GetPressure(void)
{
	double PressureValue = 0.0;
	
	PressureSampleValue[0] = pressure_GetAdcValue();
	PressureValue = pressure_Filter((uint32_t*)PressureSampleValue);

#if (PRESS_SAMPLE_RESISTOR_DIVIDED==1)
	PressureValue = PressureValue*(PRESS_SAMPLE_RESISTOR_R1+PRESS_SAMPLE_RESISTOR_R2)/PRESS_SAMPLE_RESISTOR_R2;
#endif

#if (PRESS_CALIBRATION_FACTORY_USED==1)
	PressureValue -= PRESS_ZERO_POINT_OFFSET;  //减去零点漂移
	PressureValue /= PRESS_SENSITIVITY;        //计算压力值
#else
	
#endif

	 PressureValue = PressureValue < 0 ? 0 :  PressureValue;
	return (double)PressureValue;
}

