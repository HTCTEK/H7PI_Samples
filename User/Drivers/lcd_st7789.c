#include "lcd_st7789.h"
#include "string.h"

uint8_t st7789_Buffer[ST7789_Y_SIZE][ST7789_X_SIZE*2]={0};
/***********************************************
使能LCD BACKLIGTH

***********************************************/
__weak void st7789_SetBackligth(uint8_t brightless)
{
	HAL_GPIO_WritePin(ST7789_BL,(GPIO_PinState)1);
}

/***********************************************
使能LCD

***********************************************/
__weak void st7789_Enable(void)
{
	HAL_GPIO_WritePin(ST7789_EN,(GPIO_PinState)1);
}
/***********************************************
禁用LCD

***********************************************/
__weak void st7789_Disable(void)
{
	HAL_GPIO_WritePin(ST7789_EN,(GPIO_PinState)0);
}
/***********************************************
复位

***********************************************/
__weak void st7789_Reset(void)
{
	HAL_GPIO_WritePin(ST7789_RST,(GPIO_PinState)1);
	ST7789_DELAY(10);
	HAL_GPIO_WritePin(ST7789_RST,(GPIO_PinState)0);
	ST7789_DELAY(100);
	HAL_GPIO_WritePin(ST7789_RST,(GPIO_PinState)1);
	ST7789_DELAY(10);
}
/***********************************************
使能写寄存器

***********************************************/
__weak void st7789_EnableWriteCmd(void)
{
	HAL_GPIO_WritePin(ST7789_CS,(GPIO_PinState)0);
	HAL_GPIO_WritePin(ST7789_DC,(GPIO_PinState)0);
}
/***********************************************
使能写数据

***********************************************/
__weak void st7789_EnableWriteData(void)
{
	HAL_GPIO_WritePin(ST7789_CS,(GPIO_PinState)0);
	HAL_GPIO_WritePin(ST7789_DC,(GPIO_PinState)1);
}
/***********************************************
释放写数据或者命令操作

***********************************************/
__weak void st7789_Release(void)
{
	HAL_GPIO_WritePin(ST7789_CS,(GPIO_PinState)1);
}
/***********************************************
写字节数据

***********************************************/
__weak uint8_t st7789_WriteByte(uint8_t data)
{
	uint8_t res = 0;
	#if ST7789_USE_DMA==1
	res = HAL_SPI_Transmit_DMA(&ST7789_HANDLER_SPI,&data,1);
	#else
	res = HAL_SPI_Transmit(&ST7789_HANDLER_SPI,&data,1,0xffff);
	#endif
	return (!res);
}
/***********************************************
写一段

***********************************************/
__weak uint8_t st7789_WriteBytes(uint8_t* data, uint32_t length)
{
	uint8_t res = 0;
	#if ST7789_USE_DMA==1
	res = HAL_SPI_Transmit_DMA(&ST7789_HANDLER_SPI,data,length);
	#else
	res = HAL_SPI_Transmit(&ST7789_HANDLER_SPI,data,length,0xffff);
	#endif
	return (!res);
}
/***********************************************
写命令

***********************************************/
__weak uint8_t st7789_WriteReg(uint8_t cmd)
{
	st7789_EnableWriteCmd();
	st7789_WriteByte(cmd);
	st7789_Release();
	return 1;
}
/***********************************************
写数据

***********************************************/
__weak uint8_t st7789_WriteOneData(uint8_t data)
{
	st7789_EnableWriteData();
	st7789_WriteByte(data);
	st7789_Release();
	return 1;
}
__weak uint8_t st7789_WriteData(uint8_t* data, uint32_t length)
{
	st7789_EnableWriteData();
	st7789_WriteBytes(data, length);
	st7789_Release();
	return 1;
}

/************************************************

LCD 设置坐标

***********************************************/

void st7789_SetPos(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye) 
{ 
	xs+=52;
	xe+=52;
	ys+=40;
	ye+=40;
	st7789_WriteReg(0x2a);
	st7789_WriteOneData(xs>>8);
	st7789_WriteOneData(xs&0xff);
	st7789_WriteOneData(xe>>8);
	st7789_WriteOneData(xe&0xff);
	st7789_WriteReg(0x2b);
	st7789_WriteOneData(ys>>8);
	st7789_WriteOneData(ys&0xff);
	st7789_WriteOneData(ye>>8);
	st7789_WriteOneData(ye&0xff);
	st7789_WriteReg(0x2c);
} 
/***********************************************
st7789清屏

***********************************************/
void st7789_Clear(uint16_t pixel)
{
	memset(st7789_Buffer,0,sizeof(st7789_Buffer));
	for(int x=0;x<ST7789_X_SIZE;x++)             //page loop
	{ 
		for(int y=0;y<ST7789_Y_SIZE;y++)	//column loop
		{
			st7789_Buffer[y][x*2] = pixel>>8;
			st7789_Buffer[y][x*2+1] = pixel&0xff;
		}
	}
}
/***********************************************
st7789刷新显示

***********************************************/
void st7789_FillBuffer(void)
{
	st7789_SetPos(0,0,ST7789_X_SIZE-1,ST7789_Y_SIZE-1);
	st7789_WriteData((uint8_t*)st7789_Buffer,sizeof(st7789_Buffer));
}
/***********************************************
st7789写像素点

***********************************************/
void st7789_SetPixel(uint32_t x, uint32_t y, uint16_t pixel)
{
	st7789_Buffer[y][x*2] = pixel>>8;
	st7789_Buffer[y][x*2+1] = pixel&0xff;
}
/***********************************************
st7789获取像素点

***********************************************/
uint32_t st7789_GetPixel(uint32_t x, uint32_t y)
{
	uint16_t  pixel = st7789_Buffer[y][x*2+1];
	pixel = pixel | ((uint16_t)st7789_Buffer[y][x*2])<<8;
	return pixel;
}

/***********************************************
初始化

***********************************************/
__weak void st7789_Init(void)
{
	
	
	st7789_Enable();
	st7789_Reset();
	st7789_WriteReg(0x36); 
	st7789_WriteOneData(0XC0); 
	
	st7789_WriteReg(0x3A); 
	st7789_WriteOneData(0x05);

	st7789_WriteReg(0xB2); 
	st7789_WriteOneData(0x0C);
	st7789_WriteOneData(0x0C);
	st7789_WriteOneData(0x00);
	st7789_WriteOneData(0x33);
	st7789_WriteOneData(0x33);

	st7789_WriteReg(0xB7); 
	st7789_WriteOneData(0x35); 

	st7789_WriteReg(0xBB); 
	st7789_WriteOneData(0x19);

	st7789_WriteReg(0xC0); 
	st7789_WriteOneData(0x2C);

	st7789_WriteReg(0xC2); 
	st7789_WriteOneData(0x01);

	st7789_WriteReg(0xC3); 
	st7789_WriteOneData(0x12);

	st7789_WriteReg(0xC4); 
	st7789_WriteOneData(0x20); 

	st7789_WriteReg(0xC6); 
	st7789_WriteOneData(0x0F); 

	st7789_WriteReg(0xD0); 
	st7789_WriteOneData(0xA4);
	st7789_WriteOneData(0xA1);

	st7789_WriteReg(0xE0); 
	st7789_WriteOneData(0xD0);
	st7789_WriteOneData(0x04);
	st7789_WriteOneData(0x0D);
	st7789_WriteOneData(0x11);
	st7789_WriteOneData(0x13);
	st7789_WriteOneData(0x2B);
	st7789_WriteOneData(0x3F);
	st7789_WriteOneData(0x54);
	st7789_WriteOneData(0x4C);
	st7789_WriteOneData(0x18);
	st7789_WriteOneData(0x0D);
	st7789_WriteOneData(0x0B);
	st7789_WriteOneData(0x1F);
	st7789_WriteOneData(0x23);

	st7789_WriteReg(0xE1); 
	st7789_WriteOneData(0xD0);
	st7789_WriteOneData(0x04);
	st7789_WriteOneData(0x0C);
	st7789_WriteOneData(0x11);
	st7789_WriteOneData(0x13);
	st7789_WriteOneData(0x2C);
	st7789_WriteOneData(0x3F);
	st7789_WriteOneData(0x44);
	st7789_WriteOneData(0x51);
	st7789_WriteOneData(0x2F);
	st7789_WriteOneData(0x1F);
	st7789_WriteOneData(0x1F);
	st7789_WriteOneData(0x20);
	st7789_WriteOneData(0x23);

	st7789_WriteReg( 0x21); 
	st7789_WriteReg( 0x11); 
	st7789_WriteReg( 0x29); 					
	st7789_Clear(0);
	st7789_FillBuffer();
	st7789_SetBackligth(100);
}
