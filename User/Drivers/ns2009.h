/**
  ******************************************************************************
  * @file    NS2009.h
  * @author  Taomi Tech Team
  * @brief   This file contains all the functions prototypes for the NS2009
  *          module driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 Taomi Tech.
  * All rights reserved.</center></h2>
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef NS2009_H
#define NS2009_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "I2C.h"
#include "stdlib.h"

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
/** @addtogroup NS2009
  * @{
  */

/** @addtogroup HAL
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup 
  * @{
  */



/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
#ifdef NS2009_GLOBAL
#define NS2009_Ext
#else
#define NS2009_Ext    extern
#endif  //NS2009_GLOBAL

#define NS2009_TOUCH_ERROR_RANGE                40
#define NS2009_MEASURE_TIMES                    5

#define NS2009_NOT_TOUCH                        0xFFFFFFFF


/***************** NS2009 I2C Address ******************/
#define I2C_NS2009_ADDR_WRITE                   0x90
#define I2C_NS2009_ADDR_READ                    0x91

/***************** NS2009 Command List ******************/
//12-bits ADC mode
#define I2C_NS2009_12Bits_AccelerateMode_X      0x84
#define I2C_NS2009_12Bits_AccelerateMode_Y      0x94
#define I2C_NS2009_12Bits_AccelerateMode_Z1     0xA4
#define I2C_NS2009_12Bits_AccelerateMode_Z2     0xB4

#define I2C_NS2009_LowPowerMode_X               0xC0
#define I2C_NS2009_LowPowerMode_Y               0xD0
#define I2C_NS2009_LowPowerMode_Z1              0xE0
#define I2C_NS2009_LowPowerMode_Z2              0xF0

//8-bits ADC mode
#define I2C_NS2009_8Bits_AccelerateMode_X       0x86
#define I2C_NS2009_8Bits_AccelerateMode_Y       0x96
#define I2C_NS2009_8Bits_AccelerateMode_Z1      0xA6
#define I2C_NS2009_8Bits_AccelerateMode_Z2      0xB6

#define I2C_NS2009_8Bits_LowPowerMode_X         0xC2
#define I2C_NS2009_8Bits_LowPowerMode_Y         0xD2
#define I2C_NS2009_8Bits_LowPowerMode_Z1        0xE2
#define I2C_NS2009_8Bits_LowPowerMode_Z2        0xF2



#define NS2009_TOUCH_ADC_LEFT  3904
#define NS2009_TOUCH_ADC_RIGHT 210
#define NS2009_TOUCH_ADC_UP    2688
#define NS2009_TOUCH_ADC_DOWN  300

#define PENIRQ GPIOA,GPIO_PIN_15


#define TOUCH_SAMPLES_BUF_MAX     1

typedef struct 
{
    uint8_t  touched;                     
    uint8_t  touch_point;                
    uint16_t  x[TOUCH_SAMPLES_BUF_MAX];    
    uint16_t  y[TOUCH_SAMPLES_BUF_MAX];   
	
}TouchSample_t;
/** @defgroup 
  * @{
  */




/**
  * @}
  */



/* Exported macro ------------------------------------------------------------*/
/** @defgroup Exported Macros
  * @{
  */





/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/**
  * @brief  NS2009_Read_TouchPosition
  *         Read touch screen driver IC NS2009 via I2C1, get touch point position
  *         
  * @note   
  *         
  * @param  None
  * @retval uint32_t, high 16-bits is X, low 16-bits is Y
  */
void NS2009_Read_TouchPosition(I2C_HandleTypeDef *hi2c);


uint16_t NS2009_GetX(void);


uint16_t NS2009_GetY(void);


void ns2009_Init(I2C_HandleTypeDef *hi2c);
void ns2009_DeInit(I2C_HandleTypeDef *hi2c);

uint16_t NS2009_IsPressed(void);
//NS2009_Ext uint32_t GetTouchPoint(void);

//NS2009_Ext uint8_t GetTouchPointWithDoubleConfirm(uint16_t* XPos, uint16_t* YPos);

//NS2009_Ext void BubbleSort(uint32_t *values,int length);

/* Initialization and de-initialization functions  ******************************/




/* Peripheral Control functions  ************************************************/




/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* NS2009_H */

/************************ (C) COPYRIGHT Taomi Tech *****END OF FILE****/

