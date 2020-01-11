#ifdef app_arduino

#include "app_config.h"
#include "app_arduino.h"
#include "board.h"
#include "Arduino.h"

osThreadId app_handler_arduino;
/*********************************************************************
arduino 入口

**********************************************************************/
void setup()
{
	pinMode(D26,OUTPUT);
	pinMode(D25,OUTPUT);
}

void loop()
{
	digitalWrite(D25,0);
	digitalWrite(D26,1);
	delay(100);
	digitalWrite(D25,1);
	digitalWrite(D26,0);
	delay(100);
}

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
		delay(1);
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