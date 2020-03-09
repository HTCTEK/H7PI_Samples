#include "oled.h"
#include "string.h"

uint32_t oled_width = 0;
uint32_t oled_height = 0;

uint8_t oled_Buffer[OLED_PAGE_SIZE][OLED_COL_SIZE]={0};

/***********************************************
使能OLED

***********************************************/
__weak void oled_Enable(void)
{
	HAL_GPIO_WritePin(OLED_EN,(GPIO_PinState)1);
}
/***********************************************
禁用OLED

***********************************************/
__weak void oled_Disable(void)
{
	HAL_GPIO_WritePin(OLED_EN,(GPIO_PinState)0);
}
/***********************************************
复位

***********************************************/
__weak void oled_Reset(void)
{
	HAL_GPIO_WritePin(OLED_RST,(GPIO_PinState)1);
	OLED_DELAY(1);
	HAL_GPIO_WritePin(OLED_RST,(GPIO_PinState)0);
	OLED_DELAY(10);
	HAL_GPIO_WritePin(OLED_RST,(GPIO_PinState)1);
	OLED_DELAY(1);
}
/***********************************************
使能写寄存器

***********************************************/
__weak void oled_EnableWriteCmd(void)
{
	HAL_GPIO_WritePin(OLED_CS,(GPIO_PinState)0);
	HAL_GPIO_WritePin(OLED_DC,(GPIO_PinState)0);
}
/***********************************************
使能写数据

***********************************************/
__weak void oled_EnableWriteData(void)
{
	HAL_GPIO_WritePin(OLED_CS,(GPIO_PinState)0);
	HAL_GPIO_WritePin(OLED_DC,(GPIO_PinState)1);
}
/***********************************************
释放写数据或者命令操作

***********************************************/
__weak void oled_Release(void)
{
	HAL_GPIO_WritePin(OLED_CS,(GPIO_PinState)1);
}
/***********************************************
写字节数据

***********************************************/
__weak uint8_t oled_WriteByte(uint8_t data)
{
	uint8_t res = 0;
	#if OLED_USE_DMA==1
	res = HAL_SPI_Transmit_DMA(&OLED_HANDLER_SPI,&data,1);
	#else
	res = HAL_SPI_Transmit(&OLED_HANDLER_SPI,&data,1,0xffff);
	#endif
	return (!res);
}
/***********************************************
写一段

***********************************************/
__weak uint8_t oled_WriteData(uint8_t* data, uint32_t length)
{
	uint8_t res = 0;
	#if OLED_USE_DMA==1
	res = HAL_SPI_Transmit_DMA(&OLED_HANDLER_SPI,data,length);
	#else
	res = HAL_SPI_Transmit(&OLED_HANDLER_SPI,data,length,0xffff);
	#endif
	return (!res);
}
/***********************************************
写命令

***********************************************/
__weak uint8_t oled_WriteCmd(uint8_t cmd)
{
	oled_EnableWriteCmd();
	oled_WriteByte(cmd);
	oled_Release();
	return 1;
}
/***********************************************
写数据

***********************************************/
__weak uint8_t oled_WriteOneData(uint8_t data)
{
	oled_EnableWriteData();
	oled_WriteByte(data);
	oled_Release();
	return 1;
}
/************************************************

LCD 设置坐标

***********************************************/

void oled_SetColumn(uint8_t column)
{
	column = OLED_START_COL+column;
	oled_WriteCmd(0x10|(column>>4));
	oled_WriteCmd(0x00|(column&0x0f));	 
}

void oled_SetPage(uint8_t page)
{
	page = OLED_START_PAGE+page;
	oled_WriteCmd(0xb0+page);
}

void oled_SetPos(uint8_t x, uint8_t y) 
{ 
	x = OLED_START_COL+x;
	y = OLED_START_PAGE+y;
	oled_SetColumn(x);
	oled_SetPage(y);
} 
/***********************************************
oled清屏

***********************************************/
void oled_Clear(void)
{
	uint8_t page,column;
	memset(oled_Buffer,0,sizeof(oled_Buffer));
	for(page=0;page<OLED_PAGE_SIZE;page++)             //page loop
	{ 
		oled_SetPage(OLED_START_PAGE+page);  
		oled_SetColumn(OLED_START_COL); 
		for(column=0;column<OLED_COL_SIZE;column++)	//column loop
		{
		  oled_WriteOneData(oled_Buffer[page][column]);
		}
	}
}
/***********************************************
oled铺屏

***********************************************/
void oled_Fill(void)
{
	uint8_t page,column;
	memset(oled_Buffer,0XFF,sizeof(oled_Buffer));
	for(page=0;page<OLED_PAGE_SIZE;page++)             //page loop
	{ 
		oled_SetPage(OLED_START_PAGE+page);  
		oled_SetColumn(OLED_START_COL);
		for(column=0;column<OLED_COL_SIZE;column++)	//column loop
		{
		  oled_WriteOneData(oled_Buffer[page][column]);
		}
	}
}
/***********************************************
oled铺屏buffer数据

***********************************************/
void oled_FillBuffer(void)
{
	uint8_t page,column;
	for(page=0;page<OLED_PAGE_SIZE;page++)             //page loop
	{ 
		oled_SetPage(OLED_START_PAGE+page);  
		oled_SetColumn(OLED_START_COL);
		for(column=0;column<OLED_COL_SIZE;column++)	//column loop
		{
		  oled_WriteOneData(oled_Buffer[page][column]);
		}
	}
}
/***********************************************
oled写像素点

***********************************************/
void oled_SetPixel(uint32_t x, uint32_t y, uint32_t pixel)
{
	uint32_t page = y/8;
	uint32_t bit  = y%8;
	uint8_t  page_data = oled_Buffer[page][x];
	if(pixel > 0)
	{
		page_data |= (0x01<<bit);
	}
	else
	{
		page_data &= (~(0x01<<bit));
	}
	oled_Buffer[page][x] = page_data;
	//oled_SetPos(x,page);
	//oled_WriteOneData(oled_Buffer[page][x]);	
}
/***********************************************
oled获取像素点

***********************************************/
uint32_t oled_GetPixel(uint32_t x, uint32_t y)
{
	uint32_t page = y/8;
	uint32_t bit  = y%8;
	uint8_t  pixel = oled_Buffer[page][x];
	return pixel;
}

/***********************************************
oled初始化

***********************************************/
__weak void oled_Init(uint32_t width, uint32_t height)
{
	oled_width = width;
	oled_height = height/8;
	oled_Enable();
	osDelay(10);
	oled_Reset();
	osDelay(10);
	//
	//turn off display
	oled_WriteCmd(0xae); //turn off display
	//
	//oled_WriteCmd(0x40);
	//
	//Page Addressing mode
	oled_WriteCmd(0x20); 
	//
	//50% Contrast
	oled_WriteCmd(0x81);
	oled_WriteCmd(0x80); 
	//
	//up rotation
	oled_WriteCmd(0xa0); 
	//
	//normal display
	oled_WriteCmd(0xa4);
	//
	//Normal indication A6.A7 REVERSE
	oled_WriteCmd(0xA7);
	//
	//Scan from com0~comN-1
	oled_WriteCmd(0xc0);
	//
	//multiplex ratio
	oled_WriteCmd(0xa8);
	oled_WriteCmd(0x7F);
	//
	//frequency of the internal display clocks. 
	oled_WriteCmd(0xd5);
	oled_WriteCmd(0xF0);//por0x50
	//
	//start line,col32~col95
	oled_WriteCmd(0xd3);
	oled_WriteCmd(0x20);  
	//
	//common pad output voltage
	oled_WriteCmd(0xdb);
	oled_WriteCmd(0x35);//0x40,por0x35
	//
	//This command is used to set the duration of the dis-charge and pre-charge
	oled_WriteCmd(0xd9);
	oled_WriteCmd(0x11);//por0x22
	//
	oled_Clear();
	oled_WriteCmd(0xAF);
	
}