#ifndef __LCD_ST7789_H__
#define __LCD_ST7789_H__

/***************************************************************
STM32œ‡πÿ
***************************************************************/
#include "stm32h7xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

extern  SPI_HandleTypeDef hspi4;
#define ST7789_HANDLER_SPI hspi4

#define ST7789_RST GPIOC,GPIO_PIN_13
#define ST7789_CS  GPIOE,GPIO_PIN_11
#define ST7789_EN  GPIOE,GPIO_PIN_5
#define ST7789_DC  GPIOE,GPIO_PIN_6
#define ST7789_BL  GPIOE,GPIO_PIN_15

#define ST7789_DELAY(ms) osDelay(ms)

/***************************************************************

***************************************************************/
#define ST7789_X_SIZE     135
#define ST7789_Y_SIZE     240


/***************************************************************
st7789 «˝∂Ø≈‰÷√
***************************************************************/
#define ST7789_USE_DMA     0
#define ST7789_LINK_EMWIN  1




void     st7789_Init(void);
void     st7789_FillBuffer(void);
void     st7789_SetPixel(uint32_t x, uint32_t y, uint16_t pixel);
uint32_t st7789_GetPixel(uint32_t x, uint32_t y);

#endif


