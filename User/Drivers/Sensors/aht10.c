#include "aht10.h"

static float humidity = 0.0;
static float temperature = 0.0;
/*
*
*  延时函数
*  默认使用STM32硬件延时
*  可以充定义
*
*/
__attribute__((weak)) void aht10_delay(uint32_t ms)
{
#if (AHT10_OS_USED == 0)
	HAL_Delay(ms);
#elif (AHT10_OS_USED == 1)
	osDelay(ms);
#endif
}
/*
*
*  AH1O 读
*
*/
__attribute__((weak)) uint8_t aht10_Read(uint8_t* data, uint32_t length)
{
	
	uint8_t counter  = 0;
	if(HAL_I2C_Master_Receive_IT(&AHT10_I2C,AHT10_ADDRESS,data,length) == HAL_OK)
	{
		while(i2c2_rx_ok != 1 || AHT10_I2C.State !=  HAL_I2C_STATE_READY)
		{
			aht10_delay(10);
			counter++;
			if(counter >= 10)
			{
				i2c2_rx_ok = 0;
				HAL_I2C_DeInit(&AHT10_I2C);
				HAL_I2C_Init(&AHT10_I2C);
				return 0;
			}
		}
		i2c2_rx_ok = 0;
		return 1;
	}
	else
	{
		return 0;
	}

}
/*
*
*  AH1O 写
*
*/
__attribute__((weak)) uint8_t aht10_Write(uint8_t* data,uint32_t length)
{
	
	uint8_t counter = 0;
	if(HAL_I2C_Master_Transmit_IT(&AHT10_I2C,AHT10_ADDRESS,data,length)==HAL_OK)
	{
		
		while(i2c2_tx_ok != 1 || AHT10_I2C.State !=  HAL_I2C_STATE_READY)
		{
			aht10_delay(10);
			counter++;
			if(counter >= 10)
			{
				i2c2_tx_ok = 0;
				HAL_I2C_DeInit(&AHT10_I2C);
				HAL_I2C_Init(&AHT10_I2C);
				return 0;
			}
		}
		i2c2_tx_ok = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}
/*
*
*  AH1O 读取状态寄存器
*
*/
uint8_t aht10_GetStatus(void)
{
	uint8_t data = 0;
	aht10_Read(&data,1);
	return data;
}
/*
*
*  AH1O 查询是否使能校准
*
*/
int8_t aht10_IsCalEnable(void)
{
	uint8_t data = aht10_GetStatus();
	  if((data & 0x68)==0x08)
	  return 1;
	  else  return -1;
}

/*
*
* aht10 触发测量
*/
void aht10_Trigger(void)
{
	uint8_t data[3] = {AHT10_CMD_MEASURE,0x33,0x00};
	aht10_Write(data,3);
}
/*
*
* AHT10 复位
*/
void aht10_Reset(void)
{
	uint8_t data = AHT10_CMD_RESET;
	aht10_Write(&data,1);
}


/*
*
* AHT10 读取温湿度数据
*/
void aht10_ReadData(void)
{
	uint32_t ct[2]={0};
	uint32_t RetuData = 0;
	uint16_t cnt = 0;
	uint8_t data[6]={0};


	aht10_Trigger();
	cnt = 0;
	while(((aht10_GetStatus()&0x80)==0x80))
	{
	 aht10_delay(2);
	 if(cnt++>=100)
		 {
				return;
		 }
	}

	aht10_Read(data,6);

	RetuData = (RetuData|data[1])<<8;
	RetuData = (RetuData|data[2])<<8;
	RetuData = (RetuData|data[3]);
	RetuData = RetuData >>4;
	ct[0] = RetuData;
	RetuData = 0;
	RetuData = (RetuData|data[3])<<8;
	RetuData = (RetuData|data[4])<<8;
	RetuData = (RetuData|data[5]);
	RetuData = RetuData&0xfffff;
	ct[1] =RetuData;

	humidity = (float)ct[0]*100/(1024*1024);
	temperature = (float)ct[1]*200/(1024*1024)-50;
}
/*
*
*  AH1O 初始化
*
*/
int8_t aht10_Init(void)
{
	uint32_t count = 0;
	uint8_t data[3]={0xe1,0x08,0x00};

	aht10_Write(data,3);
	while(aht10_GetStatus() == 0)
	{
		aht10_Reset();
		aht10_delay(20);
		aht10_Write(data,3);
		count++;
		if(count>=10)return -1;
		aht10_delay(500);
	}
	return 1;
}


/*
 *
 * 最大最小值去除并求平均
 *
 */


double aht10_Filter(float* data)
{
	double   sum = 0;
	double    avg = 0.0f;
	for(int i = 0; i < AHT10_FILTER_LENGTH; i++)
	{
		sum += data[i];
	}
	avg = ((double)sum)/(AHT10_FILTER_LENGTH);
	//
	//移动一位
	//
	for(int i = AHT10_FILTER_LENGTH-1; i > 0; i--)
	{
		data[i] = data[i-1];
	}
	return avg;
}
/*
*
*  获取温度
*
*/
static float HumiditySampleValue[AHT10_FILTER_LENGTH] = {0};
static float temperatureSampleValue[AHT10_FILTER_LENGTH] = {0};

float aht10_GetTemperature(void)
{
	double temperatureValue = 0.0f;
	temperatureSampleValue[0] = temperature;
	temperatureValue = aht10_Filter(temperatureSampleValue);
	return temperatureValue;
}
/*
*
*  获取湿度
*
*/
float aht10_GetHumidity(void)
{
	double humidityValue = 0.0f;
	HumiditySampleValue[0] = humidity;
	humidityValue = aht10_Filter(HumiditySampleValue);
	return humidityValue;
}
