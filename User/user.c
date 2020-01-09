#include "user.h"


/******************************************************************

�ⲿ��������


******************************************************************/
extern uint8_t retSD; /* Return value for SD */
extern char SDPath[4]; /* SD logical drive path */
extern FATFS SDFatFS; /* File system object for SD logical drive */
extern FIL SDFile; /* File object for SD */
extern uint8_t retUSER; /* Return value for USER */
extern char USERPath[4]; /* USER logical drive path */
extern FATFS USERFatFS; /* File system object for USER logical drive */
extern FIL USERFile; /* File object for USER */


/******************************************************************

�ⲿ��������


******************************************************************/
/******************************************************************

ȫ�ֱ���


******************************************************************/
DriversStatus_t drivers_status;
/******************************************************************

ϵͳ��ʼ��


******************************************************************/
void sys_Init(void)
{
	FRESULT res = 0;
	BYTE work[_MAX_SS];	
	//
	//��ʼ���ļ�ϵͳ
	//
  //retSD = FATFS_LinkDriver(&SD_Driver, SDPath);
  retUSER = FATFS_LinkDriver(&USER_Driver, USERPath);
	//
	//��ʼ��USB
	//
  MX_USB_DEVICE_Init();
	drivers_status.usb = DRIVERS_OK;
	//
	//��ʼ��SD�������ļ�ϵͳ
	//
	res = f_mount(&SDFatFS, (TCHAR const*)SDPath, 1);
	if(res!=FR_OK)
	{
		drivers_status.sdcard = DRIVERS_FAIL;
	}
	else
	{
		drivers_status.sdcard = DRIVERS_OK;
	}
	//
	//��ʼ��SPI FLASH�����ļ�ϵͳ
	//
	res = f_mount(&USERFatFS, (TCHAR const*)USERPath, 1);
	if(res != FR_OK)
	{
		res = f_mkfs(USERPath, FM_ANY,0 , work, sizeof work);
		if(res == 0)
		{
			if(f_mount(&USERFatFS, (TCHAR const*)USERPath, 1)==FR_OK)
			{
				drivers_status.spiflash = DRIVERS_OK;
			}
			else
			{
				drivers_status.spiflash = DRIVERS_FAIL;
			}
		}
		else
		{
			drivers_status.spiflash = DRIVERS_FAIL;
		}
	}
	else
	{
		drivers_status.spiflash = DRIVERS_OK;
	}
	//
  //��ʼ��UI
	//
	lcd_Init();
	#if OLED_LINK_EMWIN==1
	oled_Init(OLED_X_SIZE,OLED_Y_SIZE);
	#endif
	#if ST7789_LINK_EMWIN==1
	st7789_Init();
	#endif
	GUI_Init();
	osDelay(100);
	lcd_SetBacklight(50);
	drivers_status.gui = DRIVERS_OK;	
	//
	//��ʼ������
	//
	uart_init();
	drivers_status.uart = DRIVERS_OK;
	//APP
	#ifdef app_bengfu_3ph_PCBA_test
	{
		extern void app_b3pt_start(void);
		app_b3pt_start();
	}
	#endif	
	#ifdef app_test
	{
		extern void app_test_start(void);
		app_test_start();
	}
	#endif
	#ifdef app_test_games
	{
		extern void app_test_games_start(void);
		app_test_games_start();
	}
	#endif
}


/******************************************************************

ϵͳ�����߳�


******************************************************************/

void StartDefaultTask(void const * argument)
{
	sys_Init();
	
	while(1)
	{
		osDelay(10000);
	}

}