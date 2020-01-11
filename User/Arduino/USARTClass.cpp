/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "arduino.h"
#include "USARTClass.h"

#include "stm32f30x_usart.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"

// Public Methods //////////////////////////////////////////////////////////////
USARTClass::USARTClass(USART_Info *infoStruct,IRQn_Type irqNum)
{
	this->info=infoStruct;
	this->irqNumber=irqNum;
}

void USARTClass::begin( const uint32_t dwBaudRate )
{
	USART_TypeDef *USARTx;
	
	//set pins AF 
	uint8_t rxPin,txPin;
	uint8_t GPIO_AF_x;
	uint8_t GPIO_PinSource_RX,GPIO_PinSource_TX;
	
	USARTx=this->info->USARTx;
	rxPin=this->info->rxPin;
	txPin=this->info->txPin;
	
	GPIO_AF_x=this->info->GPIO_AF_x;
	GPIO_PinSource_RX=this->info->GPIO_PinSource_RX;
	GPIO_PinSource_TX=this->info->GPIO_PinSource_TX;
	
	
	GPIO_PinAFConfig(pInfo[rxPin].GPIOx,GPIO_PinSource_RX,GPIO_AF_x);
	GPIO_PinAFConfig(pInfo[txPin].GPIOx,GPIO_PinSource_TX,GPIO_AF_x);
	
	//set pin mode
	GPIO_InitTypeDef GPIO_InitStructer;
	
	GPIO_InitStructer.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructer.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructer.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructer.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_InitStructer.GPIO_Pin=(pInfo[rxPin].GPIO_Pin | pInfo[txPin].GPIO_Pin );
	
	GPIO_Init(pInfo[rxPin].GPIOx,&GPIO_InitStructer);
	
	//open the USARTx clock
	ClkCmdFuncPtr ptr=this->info->clkPtr;
	uint32_t PeriphClock_x=this->info->periphClock_x;
	(*ptr)(PeriphClock_x,ENABLE);

	// Configure mode,baudrate (asynchronous, no oversampling)
	USART_InitTypeDef USART_InitStructer;
	
  USART_InitStructer.USART_BaudRate=dwBaudRate;
	USART_InitStructer.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructer.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructer.USART_Parity=USART_Parity_No;
	USART_InitStructer.USART_StopBits=USART_StopBits_1;
	USART_InitStructer.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(USARTx,&USART_InitStructer);
	USART_OverSampling8Cmd(USARTx,DISABLE);
	
	// Configure interrupts
	USART_ITConfig(USARTx,USART_IT_RXNE,ENABLE);
	
	// Enable UART interrupt in NVIC
	NVIC_EnableIRQ(this->irqNumber);
	
	//Enable USART
	USART_Cmd(USARTx,ENABLE);
	
	//clean flags
	USART_ClearFlag(USARTx,USART_FLAG_TC);
	USART_ClearFlag(USARTx,USART_FLAG_TXE);
}

void USARTClass::end( void )
{
  // clear any received data
  rxBuffer.clean();

  // Disable UART interrupt in NVIC
	NVIC_DisableIRQ(this->irqNumber);

  // Wait for any outstanding data to be sent
  flush();
	
	//close it's clock 
	//open the USARTx clock
	ClkCmdFuncPtr ptr=this->info->clkPtr;
	uint32_t PeriphClock_x=this->info->periphClock_x;
	(*ptr)(PeriphClock_x,DISABLE);
}

int USARTClass::available( void )
{
  return rxBuffer.avaliable();
}

int USARTClass::peek( void )
{
  return rxBuffer.peek();
}

int USARTClass::read( void )
{
  return rxBuffer.read();
}

void USARTClass::flush( void )
{
  // Wait for transmission to complete
}

size_t USARTClass::write_ch( const uint8_t uc_data )
{
	
	USART_SendData(this->info->USARTx,uc_data);
	while (USART_GetFlagStatus(this->info->USARTx, USART_FLAG_TC) == RESET) 
	;
  return 1;
}

//interrupt handler
void USARTClass::IrqHandler( void ) 
{
	rxBuffer.store_char(USART_ReceiveData(this->info->USARTx));
}

/*
typedef struct USART_Info
{
	USART_TypeDef *USARTx;
	ClkCmdFuncPtr clkPtr;
	uint32_t periphClock_x;
	
	uint8_t txPin;
	uint8_t rxPin;
	
	uint8_t GPIO_AF_x;
	uint8_t GPIO_PinSource_TX;
	uint8_t GPIO_PinSource_RX;
}USART_Info;
*/
USART_Info USART1_Info=
{
	USART1,
	&RCC_APB2PeriphClockCmd,
	RCC_APB2Periph_USART1,
	
	PA9,
	PA10,
	
	GPIO_AF_7,
	GPIO_PinSource9,
	GPIO_PinSource10,
};
USART_Info USART2_Info=
{
	USART2,
	&RCC_APB1PeriphClockCmd,
	RCC_APB1Periph_USART2,
	
	PA2,
	PA3,
	
	GPIO_AF_7,
	GPIO_PinSource2,
	GPIO_PinSource3,
};

USART_Info USART3_Info=
{
	USART3,
	&RCC_APB1PeriphClockCmd,
	RCC_APB1Periph_USART3,
	
	PC10,
	PC11,
	
	GPIO_AF_7,
	GPIO_PinSource10,
	GPIO_PinSource11,
};


USARTClass USARTClass1(&USART1_Info,USART1_IRQn);
USARTClass USARTClass2(&USART2_Info,USART2_IRQn);
USARTClass USARTClass3(&USART3_Info,USART3_IRQn);

extern "C"{
	
	void USART1_IRQHandler()
	{
		if(USART_GetITStatus(USART1,USART_IT_RXNE))
		{
			USARTClass1.IrqHandler();
		}
	}
	void USART2_IRQHandler()
	{
		if(USART_GetITStatus(USART2,USART_IT_RXNE))
		{
			USARTClass2.IrqHandler();
		}
	}
	void USART3_IRQHandler()
	{
		if(USART_GetITStatus(USART3,USART_IT_RXNE))
		{
			USARTClass3.IrqHandler();
		}
	}
}


