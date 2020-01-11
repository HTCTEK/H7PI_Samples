#include "board.h"
/********************************************************************************
* 
*  pin map define 
*
********************************************************************************/
const uint32_t board_PinMode[]=
{
	GPIO_MODE_INPUT,	
  GPIO_MODE_OUTPUT_PP,
	GPIO_MODE_INPUT
};

const uint32_t board_PinPull[]=
{
	GPIO_NOPULL,	
  GPIO_NOPULL,
	GPIO_PULLUP
};

const PinInfo_t board_PinMap[]=
{
    //port-pin-adc-adc_ch-dac-dac_ch-uartx_-i2c-spi-tim
    //D0~D7
    {GPIOE,GPIO_PIN_3}, 
    {GPIOE,GPIO_PIN_4}, 
    {GPIOE,GPIO_PIN_5}, 
    {GPIOE,GPIO_PIN_6}, 
    {GPIOC,GPIO_PIN_13}, 
    {GPIOC,GPIO_PIN_0}, 
    {GPIOA,GPIO_PIN_2}, 
    {GPIOA,GPIO_PIN_3}, 
    //D8~D15
    {GPIOD,GPIO_PIN_10}, 
    {GPIOD,GPIO_PIN_13}, 
    {GPIOA,GPIO_PIN_8}, 
    {GPIOA,GPIO_PIN_13}, 
    {GPIOA,GPIO_PIN_14}, 
    {GPIOA,GPIO_PIN_15}, 
    {GPIOC,GPIO_PIN_11}, 
    {GPIOC,GPIO_PIN_15}, 
    //D16~D23
    {GPIOD,GPIO_PIN_2}, 
    {GPIOD,GPIO_PIN_3}, 
    {GPIOD,GPIO_PIN_6}, 
    {GPIOD,GPIO_PIN_7}, 
    {GPIOB,GPIO_PIN_5}, 
    {GPIOB,GPIO_PIN_8}, 
    {GPIOE,GPIO_PIN_0}, 
    {GPIOE,GPIO_PIN_1}, 
    //D24~D26
    {GPIOD,GPIO_PIN_9}, 
    {GPIOC,GPIO_PIN_14}, 
    {GPIOC,GPIO_PIN_15}, 
    //A0~A7
    {GPIOA,GPIO_PIN_4}, 
    {GPIOA,GPIO_PIN_5}, 
    {GPIOA,GPIO_PIN_6}, 
    {GPIOA,GPIO_PIN_7}, 
    {GPIOC,GPIO_PIN_4}, 
    {GPIOC,GPIO_PIN_5}, 
    {GPIOB,GPIO_PIN_0}, 
    {GPIOB,GPIO_PIN_1}, 
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
}

/********************************************************************************
* 
* board init
*
********************************************************************************/
void board_Init(void)
{
	
	__enable_irq();
}