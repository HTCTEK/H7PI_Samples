#include "app_config.h"
#include "DIALOG.h"

#ifdef app_test_games

void mainWin_Init(void);
void temperatureWin_Init(WM_HWIN _hParent);

osThreadId app_handler_test_games;
osThreadId app_handler_navigation;
osThreadId app_handler_sensors;
osThreadId app_handler_refresh;

uint32_t PageNum = 0;

void GUI_UserExec(void)
{
		GUI_Exec();
		st7789_FillBuffer();
}
/*********************************************************************
主要任务

**********************************************************************/
extern GUI_CONST_STORAGE GUI_BITMAP bm0;

void app_test_games_task(void const * argument)
{
	//
	//初始化LCD界面
	GUI_SelectLayer(ID_GUI_LCD);
	//
	//初始化OLED界面
	GUI_SelectLayer(ID_GUI_LCD_ST7789);
	GUI_SetOrientationEx(GUI_SWAP_XY|GUI_MIRROR_X,ID_GUI_LCD_ST7789);
	mainWin_Init();
	while(1)
	{
		GUI_UserExec();
		osDelay(10);
	}
}
/*********************************************************************
传感器任务

**********************************************************************/
void app_sensors_task(void const * argument)
{
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,1);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,1); //sensors power
	aht10_Init();
	hp203b_Init();
	bh1730_Init();
	while(1)
	{
		aht10_ReadData();
		hp203b_ReadData();
		bh1730_ReadData();
		bh1730_GetLux();
		osDelay(100);
	}
}

/*********************************************************************
刷新任务

			GUI_SelectLayer(ID_GUI_OLED);
			sprintf(tmp,"Temperature:%5.2f C",hp203b_GetTemperature());
			GUI_DispStringAt(tmp,0,0);
			sprintf(tmp,"Pressure:%5.2f kPa",hp203b_GetPressure());
			GUI_DispStringAt(tmp,0,8);
			sprintf(tmp,"Altitude:%5.2f m",hp203b_GetAltitude());
			GUI_DispStringAt(tmp,0,16);
			sprintf(tmp,"Humidity:%5.2f RH%%",aht10_GetHumidity());
			GUI_DispStringAt(tmp,0,24);
**********************************************************************/
void mainRefresh(void);
int8_t aht10_Init(void);
void app_refresh_task(void const * argument)
{
	char tmp[64]={0};
	aht10_Init();
	while(1)
	{
		switch(PageNum)
		{
			case 0:
				//mainRefresh();
				aht10_ReadData();
				memset(tmp,0,sizeof tmp);
				sprintf(tmp,"\r\ntemperature: %5.1f C\r\nhumidity: %5.1f RH%%\r\n\r\n",aht10_GetTemperature(),aht10_GetHumidity());
				cdc_printf(tmp);
				uart_send((uint8_t*)tmp,strlen(tmp));	
				led(1,0);led(2,1);
				osDelay(500);
				led(1,1);led(2,0);
				osDelay(500);
			
			break;
		}
	}
}
/*********************************************************************
导航键任务

**********************************************************************/
void app_navigation_task(void const * argument)
{
	uint8_t a1,a2,b1,b2,c1,c2,d1,d2,e1,e2;
	while(1)
	{
		a1=a2;a2=io_get(PI_IO21);
		b1=b2;b2=io_get(PI_IO22);
		c1=c2;c2=io_get(PI_IO23);
		d1=d2;d2=io_get(PI_IO24);
		e1=e2;e2=io_get(PI_IO25);
		if(a1==1&&a2==0){GUI_StoreKeyMsg(GUI_KEY_UP,1);}
		//else if(a1==0&&a2==1){GUI_StoreKeyMsg(GUI_KEY_UP,0);}
		if(b1==1&&b2==0){GUI_StoreKeyMsg(GUI_KEY_RIGHT,1);}
		//else if(b1==0&&b2==1){GUI_StoreKeyMsg(GUI_KEY_RIGHT,0);}
		if(c1==1&&c2==0){GUI_StoreKeyMsg(GUI_KEY_LEFT,1);}
		//else if(c1==0&&c2==1){GUI_StoreKeyMsg(GUI_KEY_LEFT,0);}
		if(d1==1&&d2==0){GUI_StoreKeyMsg(GUI_KEY_DOWN,1);}
		//else if(d1==0&&d2==1){GUI_StoreKeyMsg(GUI_KEY_DOWN,0);}
		if(e1==1&&e2==0){GUI_StoreKeyMsg(GUI_KEY_ENTER,1);}
		//else if(e1==0&&e2==1){GUI_StoreKeyMsg(GUI_KEY_ENTER,0);}
		
		osDelay(100);
	}
}
/*********************************************************************
任务启动

**********************************************************************/
void app_test_games_start(void)
{	

  osThreadDef(navigation_task, app_navigation_task, osPriorityNormal, 1, 256);
	app_handler_navigation = osThreadCreate(osThread(navigation_task), NULL);
	
  osThreadDef(sensors_task, app_sensors_task, osPriorityNormal, 2, 1024);
	app_handler_sensors = osThreadCreate(osThread(sensors_task), NULL);
	
  osThreadDef(test_task, app_test_games_task, osPriorityNormal, 3, 1024);
	app_handler_test_games = osThreadCreate(osThread(test_task), NULL);
	osDelay(100);
  osThreadDef(refresh_task, app_refresh_task, osPriorityNormal, 4, 1024*3);
	app_handler_refresh = osThreadCreate(osThread(refresh_task), NULL);
}

#endif