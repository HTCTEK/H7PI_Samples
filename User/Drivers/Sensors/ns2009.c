
#include "ns2009.h"


#define NS2009_GLOBAL


uint8_t touch_i2c_tx_ok = 0;
uint8_t touch_i2c_rx_ok = 0;

uint8_t X_pos[2] = {0};
uint8_t Y_pos[2] = {0};
TouchSample_t touchSamples;

void NS2009_Read_TouchPosition(I2C_HandleTypeDef *hi2c)
{
		uint8_t counter = 0;
//	if(HAL_GPIO_ReadPin(PENIRQ) == 0)
//	{
    uint8_t temp = I2C_NS2009_LowPowerMode_X;
    HAL_I2C_Master_Transmit_IT(&hi2c1,I2C_NS2009_ADDR_WRITE,&temp,1);
	  while(touch_i2c_tx_ok != 1 || hi2c->State != HAL_I2C_STATE_READY)
		{
			osDelay(10);
			counter++;
			if(counter > 10)
			{
				touch_i2c_tx_ok = 0;
				HAL_I2C_DeInit(&hi2c1);
				HAL_I2C_Init(&hi2c1);
				return;
			}
		}
		counter = 0;
		HAL_I2C_Master_Receive_IT(&hi2c1, I2C_NS2009_ADDR_READ, X_pos, 2);
	  while(touch_i2c_rx_ok != 1 || hi2c->State != HAL_I2C_STATE_READY)
		{
			osDelay(10);
			counter++;
			if(counter > 10)
			{
				touch_i2c_rx_ok = 0;
				HAL_I2C_DeInit(&hi2c1);
				HAL_I2C_Init(&hi2c1);
				return;
			}
		}
		counter = 0;

    temp = I2C_NS2009_LowPowerMode_Y;
    HAL_I2C_Master_Transmit_IT(&hi2c1,I2C_NS2009_ADDR_WRITE,&temp,1);
	  while(touch_i2c_tx_ok != 1 || hi2c->State != HAL_I2C_STATE_READY)
		{
			osDelay(10);
			counter++;
			if(counter > 10)
			{
				touch_i2c_tx_ok = 0;
				HAL_I2C_DeInit(&hi2c1);
				HAL_I2C_Init(&hi2c1);
				return;
			}
		}
		counter = 0;
		HAL_I2C_Master_Receive_IT(&hi2c1, I2C_NS2009_ADDR_READ, Y_pos,2);
	  while(touch_i2c_rx_ok != 1 || hi2c->State != HAL_I2C_STATE_READY)
		{
			osDelay(10);
			counter++;
			if(counter > 10)
			{
				touch_i2c_rx_ok = 0;
				HAL_I2C_DeInit(&hi2c1);
				HAL_I2C_Init(&hi2c1);
				return;
			}
		}
		counter = 0;
			
		touchSamples.x[0] = (((uint16_t)X_pos[0])<<4 | (uint16_t)(X_pos[1]>>4));
		touchSamples.y[0] = ((uint16_t)Y_pos[0])<<4 | ((uint16_t)Y_pos[1]>>4);
		
		if(((touchSamples.x[0] != 0)&&(touchSamples.x[0] != 4095) &&\
			 (touchSamples.y[0] != 0)&&(touchSamples.y[0] != 4095)) || (HAL_GPIO_ReadPin(PENIRQ) == 0))
		{
			touchSamples.touched = 1;
			touchSamples.touch_point = 1;
		}
		else
		{
			touchSamples.touched = 0;
			touchSamples.touch_point = 0;
		}
}


uint16_t NS2009_GetX(void)
{
	return touchSamples.x[0];
}

uint16_t NS2009_GetY(void)
{
	 return touchSamples.y[0];
}

uint16_t NS2009_IsPressed(void)
{
	 return touchSamples.touched;
}


void ns2009_Init(I2C_HandleTypeDef *hi2c)
{
	HAL_I2C_Init(hi2c);
}

void ns2009_DeInit(I2C_HandleTypeDef *hi2c)
{
	HAL_I2C_DeInit(hi2c);
}

