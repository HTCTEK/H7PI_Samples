#include "uart.h"


uart_t uart;
/***************************************************************************


****************************************************************************/
void uart_clear_buffer(void)
{
	__HAL_UART_CLEAR_IDLEFLAG(&huart);  
	HAL_UART_DMAStop(&huart); 
	uart.rxEnd = 0;
	uart.rxLength = 0;
	uart.rxNew2Usb = 0;
	uart.rxRemindBufferSize = UART_BUFFER_SIZE;
	memset(uart.rxBuffer,0,sizeof(uart.rxBuffer));
	HAL_UART_Receive_DMA(&huart,(uint8_t*)uart.rxBuffer,UART_BUFFER_SIZE);
}
/****************************************************************************


****************************************************************************/
void uart_init(void)
{
	__HAL_UART_ENABLE_IT(&huart,UART_IT_IDLE);
	uart_clear_buffer();
}
/****************************************************************************

void USART1_IRQHandler(void)
****************************************************************************/
void uart_irq_callback(void)
{
    uint32_t temp;  
	
    if(__HAL_UART_GET_FLAG(&huart,UART_FLAG_IDLE) != RESET)
    {   
			__HAL_UART_CLEAR_IDLEFLAG(&huart);  
			HAL_UART_DMAStop(&huart); 
			temp = uart.rxRemindBufferSize - __HAL_DMA_GET_COUNTER(huart.hdmarx); //上一次启动接收，剩余need2reveive的空间，所以接收need2reveive个字节，因此temp为此次相对上次接收了的字节
			
			if((uart.rxLength + temp) < UART_BUFFER_SIZE)              //接受的字节和之前的长度相加不超过buffer
			{ 
				uart.rxLength += temp ;                                  //到目前位置所有接收的字节数 	
				uart.rxRemindBufferSize = UART_BUFFER_SIZE - uart.rxLength;         //计算剩余的buffer大小
			}
			if(uart.rxLength <= 0)
			{
				uart_clear_buffer();
				return;
			}
			else
			{
				uart.rxNew2Usb = 1;
				uart.rxEnd = 1;
			}	
			HAL_UART_Receive_DMA(&huart,(uint8_t*)uart.rxBuffer+uart.rxLength,uart.rxRemindBufferSize); //从剩余的buffer位置开始接收
    }  
}
/***************************************************************************


***************************************************************************/
uint8_t uart_receive(uint32_t timeout)
{
    uint32_t counter = HAL_GetTick();
    while(__HAL_UART_GET_FLAG(&huart,UART_FLAG_TC) == RESET || __HAL_UART_GET_FLAG(&huart,UART_FLAG_TXE) == RESET){;}
				
    HAL_UART_Receive_DMA(&huart,(uint8_t*)uart.rxBuffer,UART_BUFFER_SIZE);

    while(uart.rxEnd == 0)
    {
        if(((HAL_GetTick()-counter) > timeout))
        {
            //HAL_UART_DMAStop(&huart);
            return 0;
        }
    }
    //HAL_UART_DMAStop(&huart);
    return 1;
}
/***************************************************************************

***************************************************************************/
uint8_t uart_send(uint8_t* data,uint32_t length)
{
	while(__HAL_UART_GET_FLAG(&huart,UART_FLAG_TC) == RESET || __HAL_UART_GET_FLAG(&huart,UART_FLAG_TXE) == RESET){;}
	if(HAL_UART_Transmit_DMA(&huart, data, length) == HAL_OK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}