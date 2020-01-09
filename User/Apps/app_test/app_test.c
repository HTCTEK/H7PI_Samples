#include "app_config.h"

#ifdef app_test

osThreadId app_handler_test;

/*********************************************************************


**********************************************************************/
extern GUI_CONST_STORAGE GUI_BITMAP bm0;

void app_test_task(void const * argument)
{
	while(1)
	{
		GUI_DispDecAt(uwTick,0,0,10);
		led(1,0);led(2,1);
		osDelay(500);
		led(1,1);led(2,0);
		osDelay(500);
		GUI_Clear();
	}
}

/*********************************************************************


**********************************************************************/
void app_test_start(void)
{	

  osThreadDef(test_task, app_test_task, osPriorityNormal, 1, 1024);
	app_handler_test = osThreadCreate(osThread(test_task), NULL);
}

#endif