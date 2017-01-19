#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

int main(void)
{
	int status = 0, bluetoothTrigger = 0;

	wiringPiSetup ();
	pinMode(0,OUTPUT);
	digitalWrite(0,0);
	sleep(10);
	pinMode(0, INPUT);

	bluetoothTrigger =  digitalRead (0);

	// Pulseaudio is on. Now bluetooth should be initialized.
	if(bluetoothTrigger)
		status = system("/home/pi/smart-car-code/./smart-car-bluetooth");
}
