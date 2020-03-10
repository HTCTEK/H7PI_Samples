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

#include "digital.h"

/*****************************************************************************************


pinmode setting api

*****************************************************************************************/
void pinMode( uint32_t dwPin, uint32_t dwMode )
{  
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	//gpio clk enable
	board_GpioClockEnable(dwPin);
	//gpio init
	GPIO_InitStruct.Pin = board_PinMap[dwPin].pin;
	GPIO_InitStruct.Mode = board_PinMode[dwMode];
	GPIO_InitStruct.Pull = board_PinPull[dwMode];
	GPIO_InitStruct.Speed = BOARD_GPIO_FREQ;
	HAL_GPIO_Init(board_PinMap[dwPin].gpio, &GPIO_InitStruct);
}
/*****************************************************************************************


pin digital write

*****************************************************************************************/
void digitalWrite( uint32_t dwPin, uint32_t dwVal )
{
	HAL_GPIO_WritePin(board_PinMap[dwPin].gpio,board_PinMap[dwPin].pin,(GPIO_PinState)dwVal);
}
/*****************************************************************************************


pin digital read

*****************************************************************************************/

int digitalRead( uint32_t ulPin )
{
	return HAL_GPIO_ReadPin(board_PinMap[ulPin].gpio,board_PinMap[ulPin].pin);
}
/*****************************************************************************************


pin digital toggle

*****************************************************************************************/
void digitalToggle(uint32_t dwPin)
{
	HAL_GPIO_TogglePin(board_PinMap[dwPin].gpio,board_PinMap[dwPin].pin);
}
