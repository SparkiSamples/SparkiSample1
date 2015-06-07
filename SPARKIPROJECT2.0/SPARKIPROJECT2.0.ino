#include <Sparki.h>  // include the sparki library
// We should do this in SETUP .. not Loop


void setup()
{
}
void loop()
{
    sparki.beep();       // Sparki beeps!
    delay(1000);         // wait a second (1000 milliseconds)
    
    sparki.beep();
    delay(1000);

    sparki.beep();
    delay(1000);


	sparki.moveForward();
	delay(10000);

	sparki.moveStop();
	delay(1000);
    
}




  
