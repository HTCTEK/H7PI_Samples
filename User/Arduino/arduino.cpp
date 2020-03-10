#ifdef app_arduino

#include "board.h"
#include "Arduino.h"

/*********************************************************************
arduino Èë¿Ú

**********************************************************************/

void setup(void)
{
	pinMode(D26,OUTPUT);
	pinMode(D25,OUTPUT);
}


void loop(void)
{
	uint8_t buffer[2048]={0};
	float voltage = 0;
	digitalWrite(D25,0);
	digitalWrite(D26,1);
	delay(100);
	digitalWrite(D25,1);
	digitalWrite(D26,0);
	delay(100);
	voltage = analogReadVoltage(A0);
	if(Serial.available())
	{
		int i = Serial.available();
		char tmp = 0;
		for(;i > 0;i--)
		{
			//read data and write to USB CDC one by one 
			Serial.read(&tmp,1);
			Serial.write(&tmp,1);
			delay(100);
		}
	}
}


	
#endif