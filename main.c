#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

/*
BLUETOOTH_PIN is pin number 11
GPIO 0 WiringPi 0

SHUTDOWN_PIN is pin number 13
GPIO 2 WiringPi 2

NO_EXECUTION_PIN is pin number 15
GPIO 3 WiringPi 3

DROP_CONNECTIONS_PIN is pin number 16
GPIO 4 WiringPi 4
*/

#define SHUTDOWN_REQUESTED     	 (0)
#define BLUETOOTH_REQUESTED      (1)
#define DROP_CONNECTIONS 		 (1)

#define DO_NOT_EXECUTE			 (0)
#define EXECUTE 				 (1)

// Defines for GPIO pins
#define DROP_CONNECTIONS_PIN     (4)
#define NO_EXECUTION_PIN		 (3)
#define SHUTDOWN_PIN  		 	 (2)
#define BLUETOOTH_PIN 		 	 (0)

static int bluetoothTrigger = 3, shutdownTrigger = 3, executionControl = 5;

int main(void)
{
	// Set up WiringPi and pins
	wiringPiSetup ();

	/*
	Set up exectuion control pin.
	Set to pull-up. Short to ground to stop execution.
	*/
	pullUpDnControl(NO_EXECUTION_PIN, PUD_UP);
	pinMode(NO_EXECUTION_PIN, INPUT);
 
	/*
	Set up bluetooth check pin.
	Set to pull-down. Arduino pulls high
	when bluetooth should be visible
	*/
	pullUpDnControl(BLUETOOTH_PIN,PUD_DOWN);
	pinMode(BLUETOOTH_PIN,INPUT);

	/*
	Set up shutdown check pin.
	Set to pull-up. Set low when arduino shuts down.
	*/
	pullUpDnControl(SHUTDOWN_PIN,PUD_UP);
	pinMode(SHUTDOWN_PIN,INPUT);

	/* 
	Set up drop connections pin.
	Set to pull-down. Arduino pulls high when 
	all bluetooth connections should be dropped.
	*/
	pullUpDnControl(DROP_CONNECTIONS_PIN,PUD_DOWN);
	pinMode(DROP_CONNECTIONS_PIN,INPUT);

	/*
	Reads the execution control pin every time of the loop
	This is to be able to stop execution if
	pin is shorted to ground. If zero is read stop execution
	Otherwise run main functionality
	*/
	while (1){
		// Read execution control pin
		executionControl = digitalRead(NO_EXECUTION_PIN);
		printf("Loop\n");
		if(executionControl == DO_NOT_EXECUTE){
			// Stop execution
			printf("Stop execution\n");
			return 0;
		}
		// Run main functionality reading GPIO pins
		readGPIO();
	}

	return 0;
}

void readGPIO(){
	int bluetoothPrevious = 7;

	// Read GPIO to see if bluetooth visible triggered 
	bluetoothTrigger = digitalRead(BLUETOOTH_PIN);

	// Read GPIO to see if shutdown should be triggered
	shutdownTrigger = digitalRead(SHUTDOWN_PIN);

	// Read GPIO to see if all bluetooth connections should be dropped
	dropConnectionsTrigger = digitalRead(DROP_CONNECTIONS_PIN)

	if(bluetoothPrevious == BLUETOOTH_REQUESTED){
		bluetoothTrigger = 7;
	}else{
		bluetoothPrevious = 7;
	}

	// Pulseaudio is on. Now bluetooth should be initialized.
	if(bluetoothTrigger == BLUETOOTH_REQUESTED){
		printf("Bluetooth");
		bluetoothPrevious = BLUETOOTH_REQUESTED;
		(void) system("/home/pi/bluetoothProject/./smart-car-bluetooth");
	}

	// If connection drop is triggered, drop all bluetooth connections
	if(dropConnectionsTrigger == DROP_CONNECTIONS){
		(void) system("/home/pi/bluetoothProject/./drop-bluetooth-connections");
	}

	// Shutdown procedure should begin
	if(shutdownTrigger == SHUTDOWN_REQUESTED){
		printf("Shutdown\n");
		(void) system("sudo init 0");
	}
}
