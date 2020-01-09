/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ENABLE_SD_DMA_CACHE_MAINTENANCE 1
#define DE_Pin GPIO_PIN_3
#define DE_GPIO_Port GPIOE
#define RE_Pin GPIO_PIN_4
#define RE_GPIO_Port GPIOE
#define LED_GREEN_Pin GPIO_PIN_14
#define LED_GREEN_GPIO_Port GPIOC
#define LED_RED_Pin GPIO_PIN_15
#define LED_RED_GPIO_Port GPIOC
#define FLASH_MISO_Pin GPIO_PIN_2
#define FLASH_MISO_GPIO_Port GPIOC
#define FLASH_MOSI_Pin GPIO_PIN_3
#define FLASH_MOSI_GPIO_Port GPIOC
#define PI_CE0_Pin GPIO_PIN_11
#define PI_CE0_GPIO_Port GPIOE
#define PI_SCK_Pin GPIO_PIN_12
#define PI_SCK_GPIO_Port GPIOE
#define PI_MOSI_Pin GPIO_PIN_14
#define PI_MOSI_GPIO_Port GPIOE
#define PI_CE1_Pin GPIO_PIN_15
#define PI_CE1_GPIO_Port GPIOE
#define FLASH_CS_Pin GPIO_PIN_12
#define FLASH_CS_GPIO_Port GPIOB
#define FLASH_SCK_Pin GPIO_PIN_13
#define FLASH_SCK_GPIO_Port GPIOB
#define SDMMC_CDN_Pin GPIO_PIN_8
#define SDMMC_CDN_GPIO_Port GPIOD
#define TFT_BL_Pin GPIO_PIN_6
#define TFT_BL_GPIO_Port GPIOC
#define TFT_CS_Pin GPIO_PIN_7
#define TFT_CS_GPIO_Port GPIOC
#define TFT_RST_Pin GPIO_PIN_8
#define TFT_RST_GPIO_Port GPIOC
#define IO7_Pin GPIO_PIN_11
#define IO7_GPIO_Port GPIOC
#define IO8_Pin GPIO_PIN_12
#define IO8_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
