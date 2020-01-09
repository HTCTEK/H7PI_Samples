#ifndef __FONT_EXT_H__
#define __FONT_EXT_H__

#include "stm32h7xx_hal.h"
#include "spiflash.h"
#include "fatfs.h"
#include "string.h"

#define FONT_PATH "1:/font"
#define FONT_FILE "yahei14.bin"

uint8_t font_ReadFont(uint8_t* buffer, char* font, uint32_t offset, uint32_t size);


#endif


