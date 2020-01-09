//#include "icm20648.h"
///* factor for converting a radian number to an equivalent number in degrees */
//const float RAD2DEG = 4068 / 71;

///**********************************************************************************
//*
//*  延时函数
//*  默认使用STM32硬件延时
//*  可以充定义
//*
//**********************************************************************************/
//__attribute__((weak)) void icm20648_Delay(uint32_t ms)
//{
//#if (ICM20648_USE_OS == 0)
//	HAL_Delay(ms);
//#elif (HP203B_OS_USED == 1)
//	osDelay(ms);
//#endif
//}
///**********************************************************************************
//*
//*  HP203B 读
//*
//**********************************************************************************/
//__attribute__((weak)) uint8_t icm20648_Read(uint8_t* data, uint32_t length)
//{
//	uint8_t counter  = 0;
//	if(HAL_I2C_Master_Receive_IT(&ICM20648_I2C,ICM20648_REG_ADDRESS,data,length) == HAL_OK)
//	{
//		while(i2c1_rx_ok != 1 || ICM20648_I2C.State !=  HAL_I2C_STATE_READY)
//		{
//			icm20648_Delay(10);
//			counter++;
//			if(counter >= 10)
//			{
//				i2c1_rx_ok = 0;
//				HAL_I2C_DeInit(&ICM20648_I2C);
//				HAL_I2C_Init(&ICM20648_I2C);
//				return 0;
//			}
//		}
//		i2c1_rx_ok = 0;
//		return 1;
//	}
//	else
//	{
//		return 0;
//	}
//}
///*********************************************************************************
//*
//*  HP203B 写
//*
//**********************************************************************************/
//__attribute__((weak)) uint8_t icm20648_Write(uint8_t* data,uint32_t length)
//{
//	uint8_t counter = 0;
//	if(HAL_I2C_Master_Transmit_IT(&ICM20648_I2C,ICM20648_REG_ADDRESS,data,length)==HAL_OK)
//	{
//		
//		while(i2c1_tx_ok != 1 || ICM20648_I2C.State !=  HAL_I2C_STATE_READY)
//		{
//			icm20648_Delay(10);
//			counter++;
//			if(counter >= 10)
//			{
//				i2c1_tx_ok = 0;
//				HAL_I2C_DeInit(&ICM20648_I2C);
//				HAL_I2C_Init(&ICM20648_I2C);
//				return 0;
//			}
//		}
//		i2c1_tx_ok = 0;
//		return 1;
//	}
//	else
//	{
//		return 0;
//	}
//}

///*********************************************************************************
//*
//*  ICM20648 写寄存器
//*
//**********************************************************************************/
//uint8_t icm20648_WriteReg(uint16_t reg, uint8_t value)
//{
//	uint8_t data[3]={0};
//	data[0]=(reg>>7)&0xff;
//	data[1]=reg&0xff;
//	data[2]=value;
//	return icm20648_Write(data,3);
//}

///** Probe for ICM20648 and try to initialize sensor
// *
// * @param[in] offset_mx Magnetometer X axis hard iron distortion correction.
// * @param[in] offset_my Magnetometer Y axis hard iron distortion correction.
// * @param[in] offset_mz Magnetometer Z axis hard iron distortion correction.
// * @param[in] scale_mx Magnetometer X axis soft iron distortion correction.
// * @param[in] scale_my Magnetometer Y axis soft iron distortion correction.
// * @param[in] scale_mz Magnetometer Z axis soft iron distortion correction.
// *
// * @return
// *   '1' if successful,
// *   '0' on error.
// */

//uint8_t icm20648_Init(float offset_mx, float offset_my, float offset_mz, float scale_mx, float scale_my, float scale_mz) {
//    uint8_t data[1];
//	
//	/* Reset ICM20648 */
//	//reset();
//	
//	m_offset_mx = offset_mx; m_offset_my = offset_my; m_offset_mz = offset_mz;
//	m_scale_mx = scale_mx; m_scale_my = scale_my; m_scale_mz = scale_mz;
//    /* Auto select best available clock source PLL if ready, else use internal oscillator */
//    icm20648_WriteReg(ICM20648_REG_PWR_MGMT_1, ICM20648_BIT_CLK_PLL);
//    /* PLL startup time - no spec in data sheet */
//    icm20648_Delay(10);
//    /* Reset I2C Slave module and use SPI */
//    /* Enable I2C Master I/F module */
//    icm20648_WriteReg(ICM20648_REG_USER_CTRL, ICM20648_BIT_I2C_IF_DIS | ICM20648_BIT_I2C_MST_EN);
//    /* Set I2C Master clock frequency */
//    icm20648_WriteReg(ICM20648_REG_I2C_MST_CTRL, ICM20648_I2C_MST_CTRL_CLK_400KHZ);
//    /* Read ICM20648 "Who am I" register */
//    read_register(ICM20648_REG_WHO_AM_I, 1, data);
//  
//    /* Check if "Who am I" register was successfully read */
//    if (data[0] != ICM20648_DEVICE_ID) {
//        return ERROR;
//    }
//    
//    /* Disable bypass for I2C Master interface pins */
//    enable_irq(0, 0);
//         
//    // TODO: odr_align_en to sync sample rates seems not to be necessary, at least for maximum sample rates.
//    
//    /* Configure accelerometer */
//    set_accel_bandwidth(ICM20648_ACCEL_BW_1210HZ);
//    set_accel_fullscale(ICM20648_ACCEL_FULLSCALE_8G);
//    //set_accel_sample_rate_div(...);    /* the accelerometer sample rate is 4500 Hz for ICM20648_ACCEL_BW_1210HZ */
//    
//    /* Configure gyroscope */
//    set_gyro_bandwidth(ICM20648_GYRO_BW_12100HZ);
//    set_gyro_fullscale(ICM20648_GYRO_FULLSCALE_1000DPS);
//    //set_gyro_sample_rate_div(...);    /* the gyroscope sample rate is 9000 Hz for ICM20648_GYRO_BW_12100HZ */
//    
//    
//    /* Enable Raw Data Ready interrupt */
//    enable_irq(1, 0);
//      
//    return 1;
//}