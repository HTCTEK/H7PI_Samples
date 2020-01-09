#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/*****************************************
��������
*****************************************/
#include "irq.h"
#include "led.h"
#include "lcd.h"
#include "GUI.h"
#include "fatfs.h"
#include "usb_device.h"
#include "uart.h"
#include "cdc.h"
#include "io.h"
#include "spiflash.h"
#include "cJSON.h"
#include "fifo.h"
#include "qspiflash.h"
/******************************************
expansion board ����
******************************************/
#include "bc20.h"
#include "aht10.h"
#include "hp203b.h"
#include "bh1730.h"
#include "oled.h"
#include "lcd_st7789.h"
/******************************************
��ʾ�������ã�����ID��ҪС���·��Ķ���
������������GUI_Config.h������
������Ҫ��С���󣬲��ܿ�Խ��
���磬�����ʹ��OLED,����ʹ��ST7789,
��ô7789������1������Ϊ2
#define GUI_NUM_LAYERS            3 
******************************************/
#define ID_GUI_LCD        0
#define ID_GUI_OLED       2
#define ID_GUI_LCD_ST7789 1


typedef enum
{
	DRIVERS_FAIL = 0,
	DRIVERS_OK,
	DRIVERS_STATUS_NUM
	
}DriversStatus;




typedef struct
{
	DriversStatus sdcard;
	DriversStatus gui;
	DriversStatus usb;
	DriversStatus uart;
	DriversStatus spiflash;
	
}DriversStatus_t;



extern uint8_t retSD; /* Return value for SD */
extern char SDPath[4]; /* SD logical drive path */
extern FATFS SDFatFS; /* File system object for SD logical drive */
extern FIL SDFile; /* File object for SD */
extern uint8_t retUSER; /* Return value for USER */
extern char USERPath[4]; /* USER logical drive path */
extern FATFS USERFatFS; /* File system object for USER logical drive */
extern FIL USERFile; /* File object for USER */


extern GUI_CONST_STORAGE GUI_FONT GUI_FontHZ48x48;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHZ16x16;
extern GUI_CONST_STORAGE GUI_FONT heiti14;


#endif