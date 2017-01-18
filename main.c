#include <stdlib.h>


// Pulseaudio is on. Now bluetooth should be initialized.
int status;

status = system(echo "***************************************");
status = system(echo "* Launching Bluetooth connection code *");
status = system(echo "***************************************");


status = system(/home/pi/smart-car-code/./smart-car-bluetooth);

status = system(echo "*****************************");
status = system(echo "* Bluetooth connection done *");
status = system(echo "*****************************");
