#ifndef _USART_CLASS_
#define _USART_CLASS_

#include "HardwareSerial.h"
#include "RingBuffer.h"

#include "stm32h7xx_hal.h"
#include "clockEnable.h"

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

class USARTClass : public HardwareSerial
{
  protected:
		USART_Info *info;
    IRQn_Type irqNumber;
		
		RingBuffer rxBuffer;

  public:
		USARTClass(USART_Info *infoStruct,IRQn_Type irqNum);
	
    void begin( const uint32_t dwBaudRate ) ;
    void end( void ) ;
    virtual int available( void ) ;
    virtual int peek( void ) ;
    virtual int read( void ) ;
    virtual void flush( void ) ;
    virtual size_t write_ch( const uint8_t c ) ;
	
		void IrqHandler( void ) ;
    virtual operator bool() { return true; } // UART always active
};

extern USARTClass USARTClass1; 
extern USARTClass USARTClass2;
extern USARTClass USARTClass3;
//===========TX,RX===========//
//USART1(Serial2): PA9,PA10
//USART2(Serial) : PA2,PA3
//USART3(Serial3): PC10,PC11

#define Serial 	 	USARTClass2
#define Serial2		USARTClass1
#define Serial3		USARTClass3

#endif // _UART_CLASS_
