#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

/*
BluetoothPin is pin number 11
GPIO 0 WiringPi 0

ShutdownPin is pin number 13
GPIO 2 WiringPi 2
*/

#define SHUTDOWN_REQUESTED     	 (0)
#define BLUETOOTH_REQUESTED      (1)
#define SHUTDOWN_PIN  		 	 (2)
#define BLUETOOTH_PIN 		 	 (0)

static int index = 1000;

int main(void)
{
	while (index > 0){
		index = functionality();
		printf("Loop\n");
	}

	return 0;
}

int functionality(){

// Variables
	int status = 0, bluetoothTrigger = 3, shutdownTrigger = 3;

	// Set up WiringPi
	wiringPiSetup ();

	// Set up pins
	// Bluetooth check pin
	pullUpDnControl(BLUETOOTH_PIN,PUD_DOWN);
	pinMode(BLUETOOTH_PIN,INPUT);

	// Stutdown init pin
	pullUpDnControl(SHUTDOWN_PIN,PUD_UP);
	pinMode(SHUTDOWN_PIN,INPUT);

	// Read GPIO to see if bluetooth visible triggered 
	bluetoothTrigger = digitalRead(BLUETOOTH_PIN);

	// Read GPIO to see if shutdown should be triggered
	shutdownTrigger = digitalRead(SHUTDOWN_PIN);

	// Pulseaudio is on. Now bluetooth should be initialized.
	if(bluetoothTrigger == BLUETOOTH_REQUESTED){
		status = system("/home/pi/bluetoothProject/./smart-car-bluetooth");
	}

	// Shutdown procedure should begin
	if(shutdownTrigger == SHUTDOWN_REQUESTED){
		printf("Shutdown");
		//status = system("sudo init 0");
	}

	return --index;
}