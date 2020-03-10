#ifdef app_arduino

#include "app_config.h"
#include "app_arduino.h"

osThreadId app_handler_arduino;

void setup(void);
void loop(void);
void board_Init(void);
/*********************************************************************
主要任务

**********************************************************************/
void app_arduino_task(void const * argument)
{
	board_Init();
	setup();
	while(1)
	{
		loop();
	}
}
/*********************************************************************
任务启动

**********************************************************************/
void app_arduino_start(void)
{	
  osThreadDef(arduino_task, app_arduino_task, osPriorityNormal, 1, 10240);
	app_handler_arduino = osThreadCreate(osThread(arduino_task), NULL);
}
	
#endif