#include <stdlib.h>
#include <stdio.h>


// Pulseaudio is on. Now bluetooth should be initialized.
int status = 0;
status = system("/home/pi/smart-car-code/./smart-car-bluetooth");
