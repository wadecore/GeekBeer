/*******************************************************
 *                      FRIDGE.
 *      fridge. hodor hodor fridge HOLD THE DOOR.
 * 
 *******************************************************/

#include <Servo.h>        //Include the Servo Library
#include <Bounce2.h>

Servo servo0;              //This creates an object for the Servo library, 'servo0'.
Servo servo1;              //This creates an object for the Servo library, 'servo1'.

const int DIGITAL_2_PIN = 2; // Analog Pin 3 is the fourth Rotation Knob in the system. This will be set to control the Wrist Servo on the Snapper.

Bounce buttonLeft  = Bounce();  //debouncing

void setup() 
{
  Serial.begin(9600); // This begins sending Serial Output at a baud rate of 9600, which can be read in the Serial Monitor in your Arduino IDE
  
  pinMode(DIGITAL_2_PIN, INPUT_PULLUP); // Setting Digital Pin 2 to Input
  buttonLeft.attach(DIGITAL_2_PIN);
  buttonLeft.interval(5); // interval in ms

  servo0.attach(3);  // This attaches the servo to the appropriate pin using the servo library.
  servo1.attach(5);  // This attaches the servo to the appropriate pin using the servo library.

  servo0.writeMicroseconds(2171); //Pusher Neutral
  servo1.writeMicroseconds(1200);  //Door Closed

  Serial.println("Starting Up..."); //Send some text over Serial
}

void loop() 
{

  buttonLeft.update();

  /*
   * Set Current Values of the Servos
   */

  int punchLeft  = buttonLeft.read();
  delay(2); //delay for 2 milliseconds

  /*
   * Do things with the buttons
   */
   
  //Left Punch
  if ( punchLeft == LOW ) 
  {
    servo1.writeMicroseconds(1834); //Door Open
    delay(3000); //Wait
    servo0.writeMicroseconds(1638); //Push Can out
    delay(2000); //Wait
    servo0.writeMicroseconds(2171);//Move Pusher back to Neutral
    delay(2000); //Wait
    servo1.writeMicroseconds(1200); //Close Door    
  } 
}
