#include "wiring_constants.h"
#include "wiring_digital.h"
#include "board.h"



void pinMode( uint32_t dwPin, uint32_t dwMode )
{  
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	board_GpioClockEnable(dwPin);
	GPIO_InitStruct.Pin = board_PinMap[dwPin].pin;
	GPIO_InitStruct.Mode = board_PinMode[dwMode];
	GPIO_InitStruct.Pull = board_PinPull[dwMode];
	GPIO_InitStruct.Speed = BOARD_GPIO_FREQ;
	HAL_GPIO_Init(board_PinMap[dwPin].gpio, &GPIO_InitStruct);
}

void digitalWrite( uint32_t dwPin, uint32_t dwVal )
{
	HAL_GPIO_WritePin(board_PinMap[dwPin].gpio,board_PinMap[dwPin].pin,(GPIO_PinState)dwVal);
}

int digitalRead( uint32_t ulPin )
{
	return HAL_GPIO_ReadPin(board_PinMap[ulPin].gpio,board_PinMap[ulPin].pin);
}

void digitalToggle(uint32_t dwPin)
{
	HAL_GPIO_TogglePin(board_PinMap[dwPin].gpio,board_PinMap[dwPin].pin);
}
