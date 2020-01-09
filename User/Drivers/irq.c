
#include "irq.h"

extern  I2C_HandleTypeDef hi2c2;
extern  I2C_HandleTypeDef hi2c1;

uint8_t i2c2_tx_ok = 0;
uint8_t i2c2_rx_ok = 0;

uint8_t i2c1_tx_ok = 0;
uint8_t i2c1_rx_ok = 0;


void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(hi2c == &hi2c2)
	{
		i2c2_tx_ok = 1;
	}
	else if(hi2c == &hi2c1)
	{
		
	}
}



void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(hi2c == &hi2c2)
	{
		i2c2_rx_ok = 1;
	}
	else if(hi2c == &hi2c1)
	{
		
	}
}

