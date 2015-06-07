#include <Sparki.h>  // include the sparki library
// We should do this in SETUP .. not Loop
// Loop is for continously repeating code. Setup is linear and will run only once


void setup()
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
void loop()
{

    
}
