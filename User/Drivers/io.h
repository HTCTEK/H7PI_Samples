#ifndef __IO_H_
#define __IO_H_

/*************************************************************************

STM32的相关配置

*************************************************************************/
#include "stm32h7xx_hal.h"

#define PI_GPIO0       GPIOE,GPIO_PIN_3
#define PI_GPIO0_PORT  GPIOE
#define PI_GPIO0_PIN   GPIO_PIN_3


#define PI_GPIO1       GPIOE,GPIO_PIN_4
#define PI_GPIO1_PORT  GPIOE
#define PI_GPIO1_PIN   GPIO_PIN_4


#define PI_GPIO2       GPIOE,GPIO_PIN_5
#define PI_GPIO2_PORT  GPIOE
#define PI_GPIO2_PIN   GPIO_PIN_5


#define PI_GPIO3       GPIOE,GPIO_PIN_6
#define PI_GPIO3_PORT  GPIOE
#define PI_GPIO3_PIN   GPIO_PIN_6

#define PI_GPIO4       GPIOC,GPIO_PIN_13
#define PI_GPIO4_PORT  GPIOC
#define PI_GPIO4_PIN   GPIO_PIN_13

#define PI_GPIO5       GPIOC,GPIO_PIN_0
#define PI_GPIO5_PORT  GPIOC
#define PI_GPIO5_PIN   GPIO_PIN_0

#define PI_GPIO6       GPIOA,GPIO_PIN_2
#define PI_GPIO6_PORT  GPIOA
#define PI_GPIO6_PIN   GPIO_PIN_2

#define PI_GPIO7       GPIOA,GPIO_PIN_3
#define PI_GPIO7_PORT  GPIOA
#define PI_GPIO7_PIN   GPIO_PIN_3

#define PI_GPIO21       GPIOA,GPIO_PIN_4
#define PI_GPIO21_PORT  GPIOA
#define PI_GPIO21_PIN   GPIO_PIN_4

#define PI_GPIO22       GPIOA,GPIO_PIN_5
#define PI_GPIO22_PORT  GPIOA
#define PI_GPIO22_PIN   GPIO_PIN_5

#define PI_GPIO23       GPIOA,GPIO_PIN_6
#define PI_GPIO23_PORT  GPIOA
#define PI_GPIO23_PIN   GPIO_PIN_6

#define PI_GPIO24       GPIOA,GPIO_PIN_7
#define PI_GPIO24_PORT  GPIOA
#define PI_GPIO24_PIN   GPIO_PIN_7

#define PI_GPIO25       GPIOC,GPIO_PIN_4
#define PI_GPIO25_PORT  GPIOC
#define PI_GPIO25_PIN   GPIO_PIN_4



#define PI_SPI_CE0       GPIOE,GPIO_PIN_11
#define PI_SPI_CE0_PORT  GPIOE
#define PI_SPI_CE0_PIN   GPIO_PIN_11

#define PI_SPI_CE1       GPIOE,GPIO_PIN_15
#define PI_SPI_CE1_PORT  GPIOE
#define PI_SPI_CE1_PIN   GPIO_PIN_15

#define IO7            GPIOC,GPIO_PIN_11
#define IO7_PORT       GPIOC
#define IO7_PIN        GPIO_PIN_11

#define IO8            GPIOC,GPIO_PIN_12
#define IO8_PORT       GPIOC
#define IO8_PIN        GPIO_PIN_12

typedef enum
{
	PI_IO0 = 0,
	PI_IO1,
	PI_IO2,
	PI_IO3,
	PI_IO4,
	PI_IO5,
	PI_IO6,
	PI_IO7,
	PI_IO21,
	PI_IO22,
	PI_IO23,
	PI_IO24,
	PI_IO25,
	PI_CE0,
	PI_CE1,
	H7_IO7,
	H7_IO8,
	IO_NUM
}gpio_enum_t;


typedef struct
{

	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;

}io_t;


/*************************************************************************

IO索引表

*************************************************************************/
extern io_t iolist[];

/*************************************************************************

API函数

*************************************************************************/
uint8_t io_get(gpio_enum_t io);
void    io_set(gpio_enum_t io, uint8_t state);


#endif


