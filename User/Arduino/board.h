/*
BSD 3-Clause License

Copyright (c) 2020, fuhua-chen
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __BOARD_H__
#define __BOARD_H__


#include "stdint.h"
#include "stm32h7xx_it.h"
#include "stm32h7xx_hal.h"
#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_msc.h"
#include "usbd_storage_if.h"
#include "usbd_cdc_msc.h"
#include "fatfs.h"
#include "spiflash.h"


#ifdef __cplusplus
 extern "C" {
#endif

#include "USBSerial.h"
/****************************************************************
 * 
 * board setting
 * 
 * *************************************************************/
#define BOARD_GPIO_FREQ  GPIO_SPEED_FREQ_VERY_HIGH
#define BOARD_FPU        1
#define BOARD_OS         0


#if BOARD_OS==1
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#endif
	
#define GPIO_AF_NONE       0XFFFFFFFF
	
#define ADC_DEVICE_NONE    ((ADC_TypeDef*)(0XFFFFFFFF))
#define ADC_CHANNEL_NONE   0XFFFFFFFF
#define BOARD_ADC_HANDLE   ADC1	
	
#define DAC_DEVICE_NONE    ((DAC_TypeDef*)(0XFFFFFFFF))
#define DAC_CHANNEL_NONE   0XFFFFFFFF
#define BOARD_DAC_HANDLE   DAC1	

#define SPI_DEVICE_NONE    ((SPI_TypeDef*)(0XFFFFFFFF))

#define UART_DEVICE_NONE   ((USART_TypeDef*)(0XFFFFFFFF))

#define I2C_DEVICE_NONE    ((I2C_TypeDef*)(0XFFFFFFFF))

/****************************************************************
 * 
 * arduino define
 * 
 * *************************************************************/
typedef enum
{
	LOW = 0,
	HIGH,
	PINSTATE_NUM
}PinState_t;


typedef enum
{
	//input mode
	INPUT = 0,
	INPUT_ANALOG,
  INPUT_PULLUP,
	INPUT_PULLDOWN,	
	//output mode
	OUTPUT,   
	OUTPUT_ANALOG,
	OUTPUT_OD,
	OUTPUT_OD_PULLUP,
	OUTPUT_OD_PULLDOWN,
	//
	PINMODE_NUM
}PinMode_t;

	
/****************************************************************
 * 
 * pin define
 * 
 * *************************************************************/
enum
{
    D0=0,D1,D2,D3,D4,D5,D6,D7,
    D8,D9,D10,D11,D12,D13,D14,D15,
    D16,D17,D18,D19,D20,D21,D22,D23,
		D24,D25,D26,
    A0,A1,A2,A3,A4,A5,A6,A7,
		spi_sck,spi_miso,spi_mosi,spi_ce0,spi_ce1,
		TX0,RX0,
 		SDA0,SCL0,
 		SDA1,SCL1,
};
//
//some alternate function 
//uses same pin of above enum
#define uart_tx1 D23
#define uart_rx1 D22

/****************************************************************
 * 
 * pin info define
 * 
 * *************************************************************/
typedef struct 
{
    GPIO_TypeDef*   gpio;
    uint32_t        pin;
	
		ADC_TypeDef*    adc;
    uint32_t        adc_ch;
	
		DAC_TypeDef*    dac;
    uint32_t        dac_ch;
	
		SPI_TypeDef*    spi;
		uint32_t        spi_af;
	
		USART_TypeDef*  uart;
		uint32_t        uart_af;
	
		I2C_TypeDef*    i2c;
		uint32_t        i2c_af;
	
	
}PinInfo_t;


/****************************************************************
 * 
 * on baord hardware define
 * 
 * *************************************************************/
//
//
//on board spi flash
#define FLASH_CS_PIN         GPIO_PIN_12
#define FLASH_CS_GPIO_PORT   GPIOB
#define FLASH_SCK_PIN        GPIO_PIN_13
#define FLASH_SCK_GPIO_PORT  GPIOB
#define FLASH_MISO_PIN       GPIO_PIN_2
#define FLASH_MISO_GPIO_PORT GPIOC
#define FLASH_MOSI_PIN       GPIO_PIN_3
#define FLASH_MOSI_GPIO_PORT GPIOC
	
extern uint8_t retSD; /* Return value for SD */
extern char SDPath[4]; /* SD logical drive path */
extern FATFS SDFatFS; /* File system object for SD logical drive */
extern FIL SDFile; /* File object for SD */
extern uint8_t retUSER; /* Return value for USER */
extern char USERPath[4]; /* USER logical drive path */
extern FATFS USERFatFS; /* File system object for USER logical drive */
extern FIL USERFile; /* File object for USER */

extern const uint32_t  board_PinMode[];
extern const uint32_t  board_PinPull[];
extern const PinInfo_t board_PinMap[];
extern const uint32_t  board_AdcRank[];

extern USBSerial Serial;
//
//
void MX_USB_DEVICE_Init(void);
//
//board api
void setup(void);
void loop(void);
void board_GpioClockEnable(uint32_t pin);
void board_Init(void);
void board_ErrorHandle(void);
//
//adc api
uint32_t board_AdcRead(uint32_t pin);
float    board_AdcReadVoltage(uint32_t pin);
//
//dac api

#ifdef __cplusplus
}
#endif


#endif
