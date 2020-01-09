#include "bh1730.h"

static float   lux;
const  uint8_t BH1730_GainIndex[]={1,2,64,128};
static float   bh1730_Gain = 1;
/*
*
*  延时函数
*  默认使用STM32硬件延时
*  可以充定义
*
*/
__attribute__((weak)) void bh1730_delay(uint32_t ms)
{
#if (BH1730_OS_USED == 0)
	HAL_Delay(ms);
#elif (BH1730_OS_USED == 1)
	osDelay(ms);
#endif
}

/*
*
*  BH1730_I2C 读
*
*/
__attribute__((weak)) uint8_t bh1730_Read(uint8_t* data, uint32_t length)
{
	uint8_t counter  = 0;
	if(HAL_I2C_Master_Receive_IT(&BH1730_I2C,BH1730_ADDRESS,data,length) == HAL_OK)
	{
		while(i2c2_rx_ok != 1 || BH1730_I2C.State !=  HAL_I2C_STATE_READY)
		{
			bh1730_delay(10);
			counter++;
			if(counter >= 10)
			{
				i2c2_rx_ok = 0;
				HAL_I2C_DeInit(&BH1730_I2C);
				HAL_I2C_Init(&BH1730_I2C);
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
__attribute__((weak)) uint8_t bh1730_Write(uint8_t* data,uint32_t length)
{
	uint8_t counter = 0;
	if(HAL_I2C_Master_Transmit_IT(&BH1730_I2C,BH1730_ADDRESS,data,length)==HAL_OK)
	{
		
		while(i2c2_tx_ok != 1 || BH1730_I2C.State !=  HAL_I2C_STATE_READY)
		{
			bh1730_delay(10);
			counter++;
			if(counter >= 10)
			{
				i2c2_tx_ok = 0;
				HAL_I2C_DeInit(&BH1730_I2C);
				HAL_I2C_Init(&BH1730_I2C);
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
*  BH1730 写命令
*
*/
uint8_t bh1730_WriteCmd(uint8_t cmd)
{
	uint8_t data = BH1730_CMD|cmd;
	return bh1730_Write(&data,1);
}

/*
*
*  BH1730 写寄存器
*
*/
uint8_t bh1730_WriteReg(uint8_t reg, uint8_t value)
{
	uint8_t data[2] = {BH1730_REG|reg, value};
	return bh1730_Write(data,2);
}

/*
*
*  BH1730 读取寄存器
*
*/
uint8_t bh1730_ReadReg(uint8_t reg, uint8_t* value)
{
	uint8_t res = 0;
	uint8_t data[1] = {BH1730_REG|reg};
	res =  bh1730_Write(data,1);
	res &= bh1730_Read(value,1);
	return res;
}


/*
*
*  BH1730 设置增益
*
*/
uint8_t bh1730_SetGain(uint8_t gain)
{
	uint8_t res =0;
	res = bh1730_WriteReg(BH1730_REG_GAIN,gain);
	bh1730_Gain = BH1730_GainIndex[gain];
	return res;
}

/*
*
*  BH1730 初始化
*
*/
uint8_t bh1730_Init(void)
{
	
	bh1730_WriteCmd(BH1730_CMD_RESET);
	bh1730_delay(1);
	bh1730_WriteReg(BH1730_REG_CTRL,BH1730_CONTINUOUS|BH1730_DATA_TYPE|BH1730_ADC_ENABLE|BH1730_POWER_ON);
	bh1730_WriteReg(BH1730_REG_TIMING,BH1730_ITIME);
	bh1730_WriteReg(BH1730_REG_INT,BH1730_INT_NOT_STOP|BH1730_INT_DISABLE|BH1730_INT_PERSIST_0);
	bh1730_SetGain(BH1730_GAIN_X1);
	return 1;
}
/*
*
*  BH1730 读取光照强度
*
*/
void bh1730_ReadData(void)
{
	uint8_t d0l = 0;
	uint8_t d0m = 0;
	uint8_t d1l = 0;
	uint8_t d1m = 0;
	uint16_t d0=0,d1=0;
	float ratio = 0.0;
	bh1730_ReadReg(BH1730_REG_DATA0_LSB,&d0l);
	bh1730_ReadReg(BH1730_REG_DATA0_MSB,&d0m);
	bh1730_ReadReg(BH1730_REG_DATA1_LSB,&d1l);
	bh1730_ReadReg(BH1730_REG_DATA1_MSB,&d1m);
	d0 = (((uint16_t)d0m)<<8) | d0l;
	d1 = (((uint16_t)d1m)<<8) | d1l;
	ratio = d1/d0;
	#if BH1730_DATA_TYPE==BH1730_DATA_SEL_TYPE0_1
	if (ratio<0.26) lux = ( 1.290 * d0 - 2.733 * d1 ) / bh1730_Gain * 102.6 / BH1730_ITIME_MS;
	else if (ratio<0.55) lux = ( 0.795 * d0 - 0.859 * d1 ) / bh1730_Gain * 102.6 / BH1730_ITIME_MS;
	else if (ratio<1.09) lux = ( 0.510 * d0 - 0.345 * d1 ) / bh1730_Gain * 102.6 / BH1730_ITIME_MS;
	else if (ratio<2.13) lux = ( 0.276 * d0 - 0.130 * d1 ) / bh1730_Gain * 102.6 / BH1730_ITIME_MS;
	else lux=0;
	#else
		lux = d0 / bh1730_Gain;
	#endif
	
}


/*
*
*  滤波器
*
*/
double bh1730_Filter(float* data)
{
	double   sum = 0;
	double    avg = 0.0f;
	for(int i = 0; i < BH1730_FILTER_LENGTH; i++)
	{
		sum += data[i];
	}
	avg = ((double)sum)/(BH1730_FILTER_LENGTH);
	//
	//移动一位
	//
	for(int i = BH1730_FILTER_LENGTH-1; i > 0; i--)
	{
		data[i] = data[i-1];
	}
	return avg;
}

static float luxSampleValue[BH1730_FILTER_LENGTH] = {0};

float bh1730_GetLux(void)
{
	double luxValue = 0.0f;
	luxSampleValue[0] = lux;
	luxValue = bh1730_Filter(luxSampleValue);
	return luxValue;
}



