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
#define DO_NOT_EXECUTE			 (0)
#define EXECUTE 				 (1)

// Defines for GPIO pins
#define NO_EXECUTION_PIN		 (3)
#define SHUTDOWN_PIN  		 	 (2)
#define BLUETOOTH_PIN 		 	 (0)

static int index = 80000;

int main(void)
{
	// Set up WiringPi
	wiringPiSetup ();

	// Variables
	int executionControl = 5;

	/*
	Set up pins
	*/

	// Set up exectuion control pin
	pullUpDnControl(NO_EXECUTION_PIN, PUD_UP);
	pinMode(NO_EXECUTION_PIN, INPUT);
 
	// Set up bluetooth check pin
	pullUpDnControl(BLUETOOTH_PIN,PUD_DOWN);
	pinMode(BLUETOOTH_PIN,INPUT);

	// Set up shutdown check pin
	pullUpDnControl(SHUTDOWN_PIN,PUD_UP);
	pinMode(SHUTDOWN_PIN,INPUT);

	/*
	Reads the execution control pin every time of the loop
	This is to be able to stop execution
	Pin is pull up. If zero is read stop execution
	Otherwise run main functionality
	*/
	while (index > 0){
		printf("While\n");
		// Read execution control pin
		executionControl = digitalRead(NO_EXECUTION_PIN);

		if(executionControl == DO_NOT_EXECUTE){
			// Stop execution
			printf("Stop execution\n");
			return 0;
		}
		// Run main functionality
		index = functionality();
	}

	return 0;
}

int functionality(){

	// Variables
	int bluetoothTrigger = 3, shutdownTrigger = 3;

	// Read GPIO to see if bluetooth visible triggered 
	bluetoothTrigger = digitalRead(BLUETOOTH_PIN);

	// Read GPIO to see if shutdown should be triggered
	shutdownTrigger = digitalRead(SHUTDOWN_PIN);

	// Pulseaudio is on. Now bluetooth should be initialized.
	if(bluetoothTrigger == BLUETOOTH_REQUESTED){
		printf("Bluetooth");
		(void) system("/home/pi/bluetoothProject/./smart-car-bluetooth");
	}

	// Shutdown procedure should begin
	if(shutdownTrigger == SHUTDOWN_REQUESTED){
		printf("Shutdown\n");
		(void) system("sudo init 0");
	}

	return --index;
}
