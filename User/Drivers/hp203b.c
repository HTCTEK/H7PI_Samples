#include "hp203b.h"
#include "string.h"


static float pressure;
static float temperature;
static float altitude;

/*
*
*  延时函数
*  默认使用STM32硬件延时
*  可以充定义
*
*/
__attribute__((weak)) void hp203b_delay(uint32_t ms)
{
#if (HP203B_OS_USED == 0)
	HAL_Delay(ms);
#elif (HP203B_OS_USED == 1)
	osDelay(ms);
#endif
}
/*
*
*  HP203B 读
*
*/
__attribute__((weak)) uint8_t hp203b_Read(uint8_t* data, uint32_t length)
{
	uint8_t counter  = 0;
	if(HAL_I2C_Master_Receive_IT(&HP203B_I2C,HP203B_ADDRESS,data,length) == HAL_OK)
	{
		while(i2c2_rx_ok != 1 || HP203B_I2C.State !=  HAL_I2C_STATE_READY)
		{
			hp203b_delay(10);
			counter++;
			if(counter >= 10)
			{
				i2c2_rx_ok = 0;
				HAL_I2C_DeInit(&HP203B_I2C);
				HAL_I2C_Init(&HP203B_I2C);
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
*  HP203B 写
*
*/
__attribute__((weak)) uint8_t hp203b_Write(uint8_t* data,uint32_t length)
{
	uint8_t counter = 0;
	if(HAL_I2C_Master_Transmit_IT(&HP203B_I2C,HP203B_ADDRESS,data,length)==HAL_OK)
	{
		
		while(i2c2_tx_ok != 1 || HP203B_I2C.State !=  HAL_I2C_STATE_READY)
		{
			hp203b_delay(10);
			counter++;
			if(counter >= 10)
			{
				i2c2_tx_ok = 0;
				HAL_I2C_DeInit(&HP203B_I2C);
				HAL_I2C_Init(&HP203B_I2C);
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
*  HP203B 初始化
*
*/
uint8_t hp203b_Init(void)
{
	uint8_t data = 0;
	data = HP203B_RESET;
	return hp203b_Write(&data,1);
}

/*
*
*  HP203B 触发测量
*
*/
void hp203b_Trigger(uint8_t channel, uint8_t OSR)
{
		uint8_t cmd = HP203B_CVT|channel|OSR;
		hp203b_Write(&cmd,1);
}
	
/*
*
*  HP203B 读取数据
*
*/
void hp203b_ReadData(void)
{
		uint8_t data[6] = {0}; 
		uint8_t cmd = HP203B_READ_PT;
		int32_t p,t,a;
		hp203b_Trigger(HP203B_CHANNEL_PT,HP203B_OSR_4096);
		hp203b_delay(10);
		hp203b_Write(&cmd,1);
	  hp203b_Read(data,6);		

		t = (data[0] * 65536) + (data[1] * 256) + data[2];
		p = (data[3] * 65536) + (data[4] * 256) + data[5];
		
		if((t&0xf00000)!=0)
		{
			t = -(0x1000000-t);
		}
		if((p&0xf00000)!=0)
		{
			p = -(0x1000000-p);
		}
		
		memset(data,0,6);
		cmd = HP203B_READ_A;
		hp203b_Write(&cmd,1);
	  hp203b_Read(data,3);
		
		a = (data[0] * 65536) + (data[1] * 256) + data[2];
		if((a&0xf00000)!=0)
		{
			a = -(0x1000000-a);
		}
		
		altitude = (float)a/100.0f;
		temperature = (float)t/100.0f;
		pressure = (float)p/100.0f*0.1f; //mbar to kpa
}
/*
*
*  滤波器
*
*/
double hp203b_Filter(float* data)
{
	double   sum = 0;
	double    avg = 0.0f;
	for(int i = 0; i < HP203B_FILTER_LENGTH; i++)
	{
		sum += data[i];
	}
	avg = ((double)sum)/(HP203B_FILTER_LENGTH);
	//
	//移动一位
	//
	for(int i = HP203B_FILTER_LENGTH-1; i > 0; i--)
	{
		data[i] = data[i-1];
	}
	return avg;
}

static float pressureSampleValue[HP203B_FILTER_LENGTH] = {0};
static float temperatureSampleValue[HP203B_FILTER_LENGTH] = {0};
static float altitudeSampleValue[HP203B_FILTER_LENGTH] = {0};


float hp203b_GetPressure(void)
{
	double pressureValue = 0.0f;
	pressureSampleValue[0] = pressure;
	pressureValue = hp203b_Filter(pressureSampleValue);
	return pressureValue;
}

float hp203b_GetTemperature(void)
{	
	double temperatureValue = 0.0f;
	temperatureSampleValue[0] = temperature;
	temperatureValue = hp203b_Filter(temperatureSampleValue);
	return temperatureValue;
}

float hp203b_GetAltitude(void)
{
	double altitudeValue = 0.0f;
	altitudeSampleValue[0] = altitude;
	altitudeValue = hp203b_Filter(altitudeSampleValue);
	return altitudeValue;
}

