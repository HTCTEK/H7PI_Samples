#ifndef __UART_H__
#define __UART_H__


#include "stm32h7xx_hal.h"
#include "FIFO.h"


/*************************************************



*************************************************/
extern UART_HandleTypeDef huart1;
#define huart huart1

/******************************************************************



******************************************************************/
#define UART_BUFFER_SIZE (256)


typedef struct
{
    uint32_t rxLength;
    uint32_t rxEnd;
		uint32_t rxRemindBufferSize;
    uint8_t  rxBuffer[UART_BUFFER_SIZE];
		uint8_t  rxNew2Usb;  //标记新数据到达，可回传到usb虚拟串口
}uart_t;

extern uart_t uart;



void    uart_clear_buffer(void);
void    uart_init(void);
void    uart_irq_callback(void);
uint8_t uart_receive(uint32_t timeout);
uint8_t uart_send(uint8_t* data,uint32_t length);



#endif