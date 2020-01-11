#include "Arduino.h"



void setup()
{
	pinMode(D26,OUTPUT);
	pinMode(D25,OUTPUT);
}

void loop()
{
	digitalWrite(D25,0);
	digitalWrite(D26,1);
	HAL_Delay(100);
	digitalWrite(D25,1);
	digitalWrite(D26,0);
	HAL_Delay(100);
}




int main(void)
{
	board_Init();
	setup();
	while(1)
	{
		loop();
	}
}
