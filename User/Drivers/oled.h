#ifndef __OLED_H__
#define __OLED_H__

/***************************************************************
STM32相关
***************************************************************/
#include "stm32h7xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

extern SPI_HandleTypeDef hspi4;
#define OLED_HANDLER_SPI hspi4

#define OLED_RST GPIOC,GPIO_PIN_13
#define OLED_CS  GPIOE,GPIO_PIN_11
#define OLED_EN  GPIOE,GPIO_PIN_5
#define OLED_DC  GPIOE,GPIO_PIN_6

#define OLED_DELAY(ms) osDelay(ms)

/***************************************************************
oled 型号
***************************************************************/
#define OLED_PARTNUMBER   GM6428TSWOG01

#if (OLED_PARTNUMBER == GM6428TSWOG01)
#define OLED_X_SIZE     64
#define OLED_Y_SIZE     128

#define OLED_START_COL  32
#define OLED_START_SEG  0
#define OLED_START_PAGE (OLED_START_SEG/8)

#define OLED_END_COL    (OLED_START_COL+OLED_X_SIZE)
#define OLED_END_SEG    (OLED_START_SEG+OLED_Y_SIZE)
#define OLED_END_PAGE   (OLED_END_SEG/8)

#define OLED_COL_SIZE   OLED_X_SIZE
#define OLED_COM_SIZE   OLED_Y_SIZE
#define OLED_PAGE_SIZE  (OLED_COM_SIZE/8)


#endif
/***************************************************************
oled 驱动配置
***************************************************************/
#define OLED_USE_DMA     0
#define OLED_LINK_EMWIN  0

/***************************************************************
API

***************************************************************/
void     oled_Init(uint32_t width, uint32_t height);
uint8_t  oled_WriteData(uint8_t* data, uint32_t length);
uint8_t  oled_WriteCmd(uint8_t cmd);
uint8_t  oled_WriteByte(uint8_t data);
void     oled_SetPixel(uint32_t x, uint32_t y, uint32_t pixel);
uint32_t oled_GetPixel(uint32_t x, uint32_t y);
void     oled_FillBuffer(void);
#endif


