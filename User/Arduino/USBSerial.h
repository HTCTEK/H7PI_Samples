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
#ifndef __USBSERIAL_H__
#define __USBSERIAL_H__


#include "stm32h7xx_hal.h"
#include "string.h"

#ifdef __cplusplus
extern "C"{
#endif
#include "Stream.h"
	
	
#define SERIAL_BUFFER_SIZE 2048

	
class USBSerial : public Stream
{
  public:
    USBSerial(void);
    void         begin(void);
		void         begin(uint32_t buadrate);
    void         begin(uint32_t buadrate, uint8_t config);
	
    virtual size_t write_ch(char ch);
    virtual size_t write(const char* str);
    virtual size_t write(const char* buf, size_t len);
            size_t read(char* buf,  uint32_t len);

    virtual uint32_t  available();
    virtual uint32_t  read();
    virtual uint32_t  peek();
    virtual void flush();
	
		char  rx_buffer[SERIAL_BUFFER_SIZE];
		uint32_t rx_length;
	
};



extern uint8_t  CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);
extern void     CDC_ClearBuffer(void);
extern void     CDC_ReadByte(uint8_t* des);
extern void     CDC_ReadBytes(uint8_t* des, uint32_t length);
extern uint8_t  CDC_WriteBytes(uint8_t* Buf, uint16_t Len);
extern uint32_t CDC_GetDataLength(void);
extern uint8_t* CDC_GetDataAddress(void);

#ifdef __cplusplus
}
#endif

#endif
