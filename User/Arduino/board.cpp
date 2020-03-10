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

#include "board.h"
/********************************************************************************
* 
*  pin map define 
*
********************************************************************************/
//
//
//Pin Mode 
const uint32_t board_PinMode[]=
{
	//input mode
	GPIO_MODE_INPUT,	
	GPIO_MODE_ANALOG,
	GPIO_MODE_INPUT,	
	GPIO_MODE_INPUT,	
	//output mode
  GPIO_MODE_OUTPUT_PP,
	GPIO_MODE_ANALOG,
	GPIO_MODE_OUTPUT_OD,
	GPIO_MODE_OUTPUT_OD,
	GPIO_MODE_OUTPUT_OD,	
};
//
//
//Pin Pull up or Pull down
const uint32_t board_PinPull[]=
{
	//INPUT
	GPIO_NOPULL,	
  GPIO_NOPULL,
	GPIO_PULLUP,
	GPIO_PULLDOWN,
	//OUTPUT
  GPIO_NOPULL,
  GPIO_NOPULL,
  GPIO_NOPULL,
	GPIO_PULLUP,
	GPIO_PULLDOWN,
	
};
//
//
//adc rank position,about adc
//conversion sequence
const uint32_t board_AdcRank[]=
{
	ADC_REGULAR_RANK_1,
	ADC_REGULAR_RANK_2,
	ADC_REGULAR_RANK_3,
	ADC_REGULAR_RANK_4,
	ADC_REGULAR_RANK_5,
	ADC_REGULAR_RANK_6,
	ADC_REGULAR_RANK_7,
	ADC_REGULAR_RANK_8,
	ADC_REGULAR_RANK_9,
	ADC_REGULAR_RANK_10,
	ADC_REGULAR_RANK_11,
	ADC_REGULAR_RANK_12,
	ADC_REGULAR_RANK_13,
	ADC_REGULAR_RANK_14,
	ADC_REGULAR_RANK_15,
	ADC_REGULAR_RANK_16
};
//
//
//Pin and function map
const PinInfo_t board_PinMap[]=
{
    //port-pin-adc-adc_ch-dac-dac_ch-spi-spi_af-uart-uart_af-i2c-i2c_af
    //D0~D7
    {GPIOE, GPIO_PIN_3,  ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOE, GPIO_PIN_4,  ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOE, GPIO_PIN_5,  ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOE, GPIO_PIN_6,  ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOC, GPIO_PIN_13, ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOC, GPIO_PIN_0,  ADC_DEVICE_NONE,  ADC_CHANNEL_10,   DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOA, GPIO_PIN_2,  ADC1,             ADC_CHANNEL_14,   DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOA, GPIO_PIN_3,  ADC1,             ADC_CHANNEL_15,   DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    //D8~D15
    {GPIOD, GPIO_PIN_10, ADC_DEVICE_NONE, ADC_CHANNEL_NONE,  DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOD, GPIO_PIN_13, ADC_DEVICE_NONE, ADC_CHANNEL_NONE,  DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOA, GPIO_PIN_8,  ADC_DEVICE_NONE, ADC_CHANNEL_NONE,  DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOA, GPIO_PIN_13, ADC_DEVICE_NONE, ADC_CHANNEL_NONE,  DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOA, GPIO_PIN_14, ADC_DEVICE_NONE, ADC_CHANNEL_NONE,  DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOA, GPIO_PIN_15, ADC_DEVICE_NONE, ADC_CHANNEL_NONE,  DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOC, GPIO_PIN_11, ADC_DEVICE_NONE, ADC_CHANNEL_NONE,  DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOC, GPIO_PIN_12, ADC_DEVICE_NONE, ADC_CHANNEL_NONE,  DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    //D16~D21
    {GPIOD, GPIO_PIN_2,  ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOD, GPIO_PIN_3,  ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOD, GPIO_PIN_6,  ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOD, GPIO_PIN_7,  ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE},
    {GPIOB, GPIO_PIN_5,  ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOB, GPIO_PIN_9,  ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE},
    //D22(uart1_rx),D23(uart1_tx)
		{GPIOE, GPIO_PIN_0,  ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART8,            GPIO_AF8_UART8,  I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOE, GPIO_PIN_1,  ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART8,            GPIO_AF8_UART8,  I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    //D24~D26
    {GPIOD, GPIO_PIN_9,  ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOC, GPIO_PIN_14, ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOC, GPIO_PIN_15, ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    //A0~A7
    {GPIOA, GPIO_PIN_4,  ADC1,             ADC_CHANNEL_18,   DAC1,            DAC_CHANNEL_1,    SPI1,            GPIO_AF5_SPI1, UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE},
    {GPIOA, GPIO_PIN_5,  ADC1,             ADC_CHANNEL_19,   DAC1,            DAC_CHANNEL_2,    SPI1,            GPIO_AF5_SPI1, UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE},
    {GPIOA, GPIO_PIN_6,  ADC1,             ADC_CHANNEL_3,    DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI1,            GPIO_AF5_SPI1, UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE},
    {GPIOA, GPIO_PIN_7,  ADC1,             ADC_CHANNEL_7,    DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI1,            GPIO_AF5_SPI1, UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE},
    {GPIOC, GPIO_PIN_4,  ADC1,             ADC_CHANNEL_4,    DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI1,            GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE},
    {GPIOC, GPIO_PIN_5,  ADC1,             ADC_CHANNEL_8,    DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI1,            GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOB, GPIO_PIN_0,  ADC1,             ADC_CHANNEL_9,    DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI1,            GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
    {GPIOB, GPIO_PIN_1,  ADC1,             ADC_CHANNEL_5,    DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI1,            GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
		//spi_sck,spi_miso,spi_mosi,spi_ce0,spi_ce1
		{GPIOE, GPIO_PIN_12, ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI4,            GPIO_AF5_SPI4, UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
		{GPIOE, GPIO_PIN_13, ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI4,            GPIO_AF5_SPI4, UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
		{GPIOE, GPIO_PIN_14, ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI4,            GPIO_AF5_SPI4, UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
		{GPIOE, GPIO_PIN_11, ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI4,            GPIO_AF5_SPI4, UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
		{GPIOE, GPIO_PIN_15, ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI4,            GPIO_AF5_SPI4, UART_DEVICE_NONE, GPIO_AF_NONE,    I2C_DEVICE_NONE, GPIO_AF_NONE}, 
		//uart0(tx,rx)
		{GPIOA, GPIO_PIN_9,  ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  USART1,           GPIO_AF7_USART1, I2C_DEVICE_NONE, GPIO_AF_NONE}, 
		{GPIOA, GPIO_PIN_10, ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  USART1,           GPIO_AF7_USART1, I2C_DEVICE_NONE, GPIO_AF_NONE}, 
		//i2c0,(sda,scl)
		{GPIOB, GPIO_PIN_7,  ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C1,            GPIO_AF4_I2C1}, 
		{GPIOB, GPIO_PIN_8,  ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C1,            GPIO_AF4_I2C1}, 
		//i2c1,(sda,scl)
		{GPIOB, GPIO_PIN_11, ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C2,            GPIO_AF4_I2C2}, 
		{GPIOB, GPIO_PIN_10, ADC_DEVICE_NONE,  ADC_CHANNEL_NONE, DAC_DEVICE_NONE, DAC_CHANNEL_NONE, SPI_DEVICE_NONE, GPIO_AF_NONE,  UART_DEVICE_NONE, GPIO_AF_NONE,    I2C2,            GPIO_AF4_I2C2}, 
		
		
};
/********************************************************************************
* 
* gpio clock enable
*
********************************************************************************/
void board_GpioClockEnable(uint32_t pin)
{
  switch((uint32_t)board_PinMap[pin].gpio)
  {
  case (uint32_t)GPIOA:
    __HAL_RCC_GPIOA_CLK_ENABLE();
    break;
  case (uint32_t)GPIOB:
    __HAL_RCC_GPIOB_CLK_ENABLE();
    break;
  case (uint32_t)GPIOC:
    __HAL_RCC_GPIOC_CLK_ENABLE();
    break;
  case (uint32_t)GPIOD:
    __HAL_RCC_GPIOD_CLK_ENABLE();
    break;
  case (uint32_t)GPIOE:
    __HAL_RCC_GPIOE_CLK_ENABLE();
    break;
  case (uint32_t)GPIOF:
    __HAL_RCC_GPIOF_CLK_ENABLE();
    break;
  case (uint32_t)GPIOG:
    __HAL_RCC_GPIOG_CLK_ENABLE();
    break;
  case (uint32_t)GPIOH:
    __HAL_RCC_GPIOH_CLK_ENABLE();
    break;
  
  default:
    break;
  }
}/********************************************************************************
* 
* adc clock enable
*
********************************************************************************/
void board_AdcClockEnable(uint32_t pin)
{
  switch((uint32_t)board_PinMap[pin].adc)
  {
  case (uint32_t)ADC1:
    __HAL_RCC_ADC12_CLK_ENABLE();
    break;
  case (uint32_t)ADC2:
    __HAL_RCC_ADC12_CLK_ENABLE();
    break;
  case (uint32_t)ADC3:
    __HAL_RCC_ADC3_CLK_ENABLE();
    break;
  
  default:
    break;
  }
}
/********************************************************************************
* 
* DAC clock enable
*
********************************************************************************/
void board_DacClockEnable(uint32_t pin)
{
  switch((uint32_t)board_PinMap[pin].dac)
  {
  case (uint32_t)DAC1:
    __HAL_RCC_ADC12_CLK_ENABLE();
    break;
  default:
    break;
  }
}
/********************************************************************************
* 
* SPI clock enable
*
********************************************************************************/
void board_SpiClockEnable(uint32_t pin)
{
  switch((uint32_t)board_PinMap[pin].spi)
  {
  case (uint32_t)SPI1:
    __HAL_RCC_SPI1_CLK_ENABLE();
    break;
  case (uint32_t)SPI2:
    __HAL_RCC_SPI2_CLK_ENABLE();
    break;
  case (uint32_t)SPI3:
    __HAL_RCC_SPI3_CLK_ENABLE();
    break;
  case (uint32_t)SPI4:
    __HAL_RCC_SPI4_CLK_ENABLE();
    break;
  case (uint32_t)SPI5:
    __HAL_RCC_SPI5_CLK_ENABLE();
    break;
  case (uint32_t)SPI6:
    __HAL_RCC_SPI6_CLK_ENABLE();
    break;
  
  default:
    break;
  }
}

/********************************************************************************
* 
* ADC default init
* will be called in board_Init()
*
********************************************************************************/
ADC_HandleTypeDef hadc;
uint32_t          adc_cali_factor = 0;

void board_AdcInit(void)
{	
  ADC_MultiModeTypeDef multimode = {0};
	hadc.Instance = BOARD_ADC_HANDLE;
	hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
	hadc.Init.Resolution = ADC_RESOLUTION_16B;
	hadc.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	hadc.Init.LowPowerAutoWait = DISABLE;
	hadc.Init.ContinuousConvMode = DISABLE;
	hadc.Init.NbrOfConversion = 1;
	hadc.Init.DiscontinuousConvMode = DISABLE;
	hadc.Init.NbrOfDiscConversion = 0;
	hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
	hadc.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
	hadc.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
	hadc.Init.OversamplingMode = ENABLE;
  hadc.Init.Oversampling.Ratio = 1023;
  hadc.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_NONE;
  hadc.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
  hadc.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;
	if (HAL_ADC_Init(&hadc) != HAL_OK)
	{
		board_ErrorHandle();
	}
	HAL_ADCEx_Calibration_Start(&hadc,ADC_CALIB_OFFSET,ADC_SINGLE_ENDED);
	adc_cali_factor = HAL_ADCEx_Calibration_GetValue(&hadc,ADC_SINGLE_ENDED);

}
/********************************************************************************
* 
* adc read,
* will be call in arduino api analogRead();
*
********************************************************************************/
uint32_t board_AdcRead(uint32_t pin)
{
	uint32_t counter = 0;
	static __IO uint32_t adcValue = 0;
	ADC_ChannelConfTypeDef sConfig = {0};	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	//adc channel config
	if(board_PinMap[pin].adc_ch != ADC_CHANNEL_NONE)
	{
		//gpio clk enable
		board_AdcClockEnable(pin);
		board_GpioClockEnable(pin);
		//gpio init
		GPIO_InitStruct.Pin = board_PinMap[pin].pin;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(board_PinMap[pin].gpio, &GPIO_InitStruct);
		
		sConfig.Channel = board_PinMap[pin].adc_ch;
		sConfig.Rank = ADC_REGULAR_RANK_1;
		sConfig.SamplingTime = ADC_SAMPLETIME_810CYCLES_5;
		sConfig.SingleDiff = ADC_SINGLE_ENDED;
		sConfig.OffsetNumber = ADC_OFFSET_NONE;
		sConfig.Offset = 0;
		if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
		{
			board_ErrorHandle();
		}
		HAL_ADC_Start(&hadc);
		HAL_ADC_PollForConversion(&hadc, 10);
		adcValue = HAL_ADC_GetValue(&hadc);
		return adcValue;
	}
	return 0;
}
/********************************************************************************
* 
* adc read voltage
* will be call in arduino api analogReadVoltage();
*
********************************************************************************/
float board_AdcReadVoltage(uint32_t pin)
{
	uint32_t value = 0;
	float    voltage = 0.0;
	value = board_AdcRead(pin);
	voltage = (float)((((double)value)/1024)*3.24/65535);
	return voltage;
}
/********************************************************************************
* 
* spi default init
* will be called in board_Init()
*
********************************************************************************/
void board_SpiInit(uint32_t sck,uint32_t miso, uint32_t mosi, uint32_t ce)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(board_PinMap[sck].spi==board_PinMap[miso].spi && board_PinMap[miso].spi==board_PinMap[mosi].spi && board_PinMap[mosi].spi != SPI_DEVICE_NONE)
	{
		board_GpioClockEnable(sck);board_GpioClockEnable(miso);board_GpioClockEnable(mosi);board_GpioClockEnable(ce);
		board_SpiClockEnable(sck);
		
		GPIO_InitStruct.Pin = board_PinMap[sck].pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = BOARD_GPIO_FREQ;
    GPIO_InitStruct.Alternate = board_PinMap[sck].spi_af;
		HAL_GPIO_Init(board_PinMap[sck].gpio, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = board_PinMap[miso].pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = BOARD_GPIO_FREQ;
    GPIO_InitStruct.Alternate = board_PinMap[sck].spi_af;
		HAL_GPIO_Init(board_PinMap[miso].gpio, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = board_PinMap[mosi].pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = BOARD_GPIO_FREQ;
    GPIO_InitStruct.Alternate = board_PinMap[sck].spi_af;
		HAL_GPIO_Init(board_PinMap[mosi].gpio, &GPIO_InitStruct);
		
		if(board_PinMap[ce].spi_af != GPIO_AF_NONE)
		{
			GPIO_InitStruct.Pin = board_PinMap[ce].pin;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			GPIO_InitStruct.Speed = BOARD_GPIO_FREQ;
			HAL_GPIO_Init(board_PinMap[ce].gpio, &GPIO_InitStruct);
		}
		else
		{
			GPIO_InitStruct.Pin = board_PinMap[ce].pin;
			GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = BOARD_GPIO_FREQ;
			GPIO_InitStruct.Alternate = board_PinMap[sck].spi_af;
			HAL_GPIO_Init(board_PinMap[ce].gpio, &GPIO_InitStruct);
		}
	}
	
}

/********************************************************************************
* 
* board error handle
*
********************************************************************************/
void board_ErrorHandle(void)
{
	while(1)
	{
		
	}
}
/********************************************************************************
* 
* on board spi flash init
* 
*
********************************************************************************/
void board_FlashInit(void)
{
	extern SPI_HandleTypeDef hspi2;
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* SPI2 clock enable */
	__HAL_RCC_SPI2_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	/**SPI2 GPIO Configuration    
	PC2_C     ------> SPI2_MISO
	PC3_C     ------> SPI2_MOSI
	PB13     ------> SPI2_SCK 
	PB12     ------> SPI2_CS
	*/
	GPIO_InitStruct.Pin = FLASH_MISO_PIN|FLASH_MOSI_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(FLASH_MISO_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = FLASH_SCK_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(FLASH_SCK_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = FLASH_CS_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(FLASH_CS_GPIO_PORT, &GPIO_InitStruct);
	//
	//SPI
	hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 0x0;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  hspi2.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi2.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi2.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi2.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi2.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi2.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi2.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi2.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE;
  hspi2.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    board_ErrorHandle();
  }
	W25Q64_SPI_Init();
}
/********************************************************************************
* 
* on board SD Card init
* 
*
********************************************************************************/
void board_SDCardInit(void)
{
	extern SD_HandleTypeDef hsd2;
  GPIO_InitTypeDef GPIO_InitStruct = {0};
	
  hsd2.Instance = SDMMC2;
  hsd2.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hsd2.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hsd2.Init.BusWide = SDMMC_BUS_WIDE_4B;
  hsd2.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd2.Init.ClockDiv = 1;
  __HAL_RCC_SDMMC2_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF9_SDIO2;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF9_SDIO2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF9_SDIO2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(SDMMC2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(SDMMC2_IRQn);

}


/********************************************************************************
* 
* on board fatfs init
*
********************************************************************************/
void board_FileSystemInit(void)
{
	static __IO FRESULT res = FR_NOT_READY;
  retSD = FATFS_LinkDriver(&SD_Driver, SDPath);
  retUSER = FATFS_LinkDriver(&USER_Driver, USERPath);
	res = f_mount(&USERFatFS, (TCHAR const*)USERPath, 1);
	if(res!= FR_OK)
	{
		board_ErrorHandle();
	}	
	res = f_mount(&SDFatFS, (TCHAR const*)SDPath, 1);
	if(res!= FR_OK)
	{
		board_ErrorHandle();
	}
}

/********************************************************************************
* 
* on board USB init
*
********************************************************************************/

void board_UsbInit(void)
{
  extern USBD_HandleTypeDef hUsbDeviceFS;
  if (USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS) != USBD_OK)
  {
    board_ErrorHandle();
  }
  if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_COMPOSITE) != USBD_OK)
  {
    board_ErrorHandle();
  }
  if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
  {
    board_ErrorHandle();
  }
}

/********************************************************************************
* 
* board init
*
********************************************************************************/
USBSerial Serial;

void board_Init(void)
{
	__enable_irq();
	board_AdcInit();
	board_FlashInit();
	board_SDCardInit();
	board_FileSystemInit();
	board_UsbInit();
}

