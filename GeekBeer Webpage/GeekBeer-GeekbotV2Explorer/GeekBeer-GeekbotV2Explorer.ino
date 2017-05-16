/***********************************************************************************
 *  RobotGeek GeekBeer V2 Line Navigator
 *            _.._..,_,_
 *           (          )
 *            ]~,"-.-~~[
 *          .=])' (;  ([
 *          | ]:: '    [
 *          '=]): .)  ([
 *            |:: '    |
 *             ~~----~~
 *         __________________
 *          |              |
 *          |     ___      |
 *         _|____/___\ ____|_
 *          \_/  \___/   \_/
 *
 *  Wiring
 *
 *    Rotation Knob - Analog Pin 0
 *    Left Servo - Digital Pin 10
 *    Right Servo - Digital Pin 11
 *    Buzzer - Digital Pin 12
 *    IR Receiver - Digital Pin 2
 *    Right LED - Digital Pin 4
 *    Left LED - Digital Pin 7
 *    Line Sensor Array - I2C
 *    LCD (4 line) - I2C
 *    LCD Up Button - Digital Pin 3
 *    LCD Down Button - Digital Pin 9
 *    LCD Play Button - Digital Pin 1
 *    LCD Stop Button - Digital Pin 8
 *
 *    Jumper for pins 9/10/11 should be set to 'VIN'
 *    Jumper for pins 3/5/6 should be set to '5V'
 *
 *  Control Behavior:
 *
 *    Put it on a line and use the LCD panel to navigate between destinations.
 *    Use the Rotation Knob to adjust forward driving trim.
 *    Customize your nagivation routes in myMap.cpp
 *
 *  External Resources
 *
 ***********************************************************************************/

#include <PiezoEffects.h>

/* GeekBot API */
#include "GeekBot.h"
/* Robot Config Parameters */
#include "Config.h"
#include "LineFollower.h"
#include "Navigation.h"

int val;

GeekBot myGeekBot; // Create GeekBot object, named myGeekBot

void setup()
{
  Serial.begin(115200);
  Serial.println("Geekbot Navigator Starting...");

  myGeekBot.init();
  delay(1000);
  myGeekBot.sound(soundUp);

}

void loop()
{
  // Loop is used entirely to read from serial awaiting command.
  int incoming = Serial.available();  
  if (incoming > 0)
  {
   val = Serial.parseInt();  //Reads integers as integer rather than ASCII. Anything else returns 0
   Serial.println(val);
   if (val == 7080)      // Get Matt a Budweiser
   {
    sendBusy();
    Beer0(); // Gets Budweiser from Home Position 
    sendBusy();
    Name0(); // Goes from Beer Fridge to Matt
    sendDone();
   }
   else if (val == 7180) // Get Rick a Budweiser
   {
    sendBusy();
    Beer0(); // Gets Budweiser from Home Position 
    sendBusy();
    Name1(); // Goes from Beer Fridge to Rick
    sendDone();
   }
   else if (val == 7280) // Get Kevin a Budweiser
   {
    sendBusy();
    Beer0(); // Gets Budweiser from Home Position 
    sendBusy();
    Name2(); // Goes from Beer Fridge to Kevin
    sendDone();
   }
   else if (val == 7380) // Get Wade a Budweiser
   {
    sendBusy();
    Beer0(); // Gets Budweiser from Home Position 
    sendBusy();
    Name3(); // Goes from Beer Fridge to Wade
    sendDone();
   }
   else if (val == 7081) // Get Matt a Bud Light
   {
    sendBusy();
    Beer1(); // Gets Bud Light from Home Position 
    sendBusy();
    Name0(); // Goes from Beer Fridge to Matt
    sendDone();
   }
   else if (val == 7181) // Get Rick a Bud Light
   {
    sendBusy();
    Beer1(); // Gets Bud Light from Home Position
    sendBusy();
    Name1(); // Goes from Beer Fridge to Rick
    sendDone();
   }
   else if (val == 7281) // Get Kevin a Bud Light
   {
    sendBusy();
    Beer1(); // Gets Bud Light from Home Position
    sendBusy();
    Name2(); // Goes from Beer Fridge to Kevin
    sendDone();
   }
   else if (val == 7381) // Get Wade a Bud Light
   {
    sendBusy();
    Beer1(); // Gets Bud Light from Home Position
    sendBusy();
    Name3(); // Goes from Beer Fridge to Wade
    sendDone();
   }
   else if (val == 7082) // Get Matt a Rolling Rock
   {
    sendBusy();
    Beer2(); // Gets Rolling Rock from Home Position
    sendBusy();
    Name0(); // Goes from Beer Fridge to Matt
    sendDone();
   }
   else if (val == 7182) // Get Rick a Rolling Rock
   {
    sendBusy();
    Beer2(); // Gets Rolling Rock from Home Position
    sendBusy();
    Name1(); // Goes from Beer Fridge to Rick
    sendDone();
   }
   else if (val == 7282) // Get Kevin a Rolling Rock
   {
    sendBusy();
    Beer2(); // Gets Rolling Rock from Home Position
    sendBusy();
    Name2(); // Goes from Beer Fridge to Kevin
    sendDone();
   }
   else if (val == 7382) // Get Wade a Rolling Rock
   {
    sendBusy();
    Beer2(); // Gets Rolling Rock from Home Position
    sendBusy();
    Name3(); // Goes from Beer Fridge to Wade
    sendDone();
   }

  }
}

// Start Command list

void Beer0() // Get Budweiser
{
  myGeekBot.sound(soundWhistle);
  myGeekBot.lineFollow(NAV_RIGHT); //Follow Line until Intersection, state = NAV_CMD for next action.
  getBeer();
  myGeekBot.lineFollow(NAV_LEFT);
}

void Beer1() // Get Bud Light
{
  myGeekBot.sound(soundWhistle);
  myGeekBot.lineFollow(NAV_RIGHT); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  getBeer();
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_LEFT);
}

void Beer2() // Get Rolling Rock
{
  myGeekBot.sound(soundWhistle);
  myGeekBot.lineFollow(NAV_RIGHT); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  getBeer();
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_LEFT);
}

void Name0() // Go to Matt, Deliver beer, back to Home
{
  myGeekBot.lineFollow(NAV_RIGHT); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  sWUT();
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_LEFT); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_STOP); //Follow Line until Intersection, state = NAV_CMD for next action.
}

void Name1() // Go to Rick, Deliver beer, back to Home
{
  myGeekBot.lineFollow(NAV_RIGHT); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  sWUT();
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_LEFT); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_STOP); //Follow Line until Intersection, state = NAV_CMD for next action.
}

void Name2() // Go to Kevin, Deliver beer, back to Home
{
  myGeekBot.lineFollow(NAV_RIGHT); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_RIGHT); //Follow Line until Intersection, state = NAV_CMD for next action.
  sWUT();
  myGeekBot.lineFollow(NAV_LEFT); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_LEFT); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_STOP); //Follow Line until Intersection, state = NAV_CMD for next action.
}

void Name3() // Go to Wade, Deliver beer, back to Home
{
  myGeekBot.lineFollow(NAV_RIGHT); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_LEFT); //Follow Line until Intersection, state = NAV_CMD for next action.
  sWUT();
  myGeekBot.lineFollow(NAV_RIGHT); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_LEFT); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_STOP); //Follow Line until Intersection, state = NAV_CMD for next action.
}

void getBeer() // Motions for getting a beer
{
  myGeekBot.lineFollow(NAV_LEFT); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_STOP);
  myGeekBot.sound(soundDown);
  myGeekBot.timedDrive(350, 50);
  delay(3000);
  myGeekBot.timedDrive(1500, -50);
  delay(1000);
  myGeekBot.timedRotate(500, 50);
  myGeekBot.recoverLine(1); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_RIGHT); //Follow Line until Intersection, state = NAV_CMD for next action.
}

void sWUT() // Stop, wait for person to take beer, U-Turn
{
  myGeekBot.lineFollow(NAV_STOP); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.sound(soundWhistle);
  delay(5000); //pause delay in mS
  myGeekBot.lineFollow(NAV_UTURN); //Follow Line until Intersection, state = NAV_CMD for next action.
}

void sendBusy() //Send busy Command to ESP
{
  Serial.println ("1111");
}

void sendDone() //Send Done Command to ESP
{
  Serial.println ("9999");
  return;
}

//void customFunction()
//{
//  myGeekBot.timedRotate(2000, 50); // time in mS, rotation speed CCW -100 to CW +100
//  delay(2000); //pause delay in mS
//  myGeekBot.timedDrive(3000, 50); //time in mS, travel speed -100 to 100
//  delay(3000); //pause delay in mS
//  myGeekBot.recoverLine(1); //Follow Line until Intersection, state = NAV_CMD for next action.
//  myGeekBot.sound(soundWhistle);
//  myGeekBot.lineFollow(NAV_LEFT); //Follow Line until Intersection, state = NAV_CMD for next action.
//  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
//  myGeekBot.lineFollow(NAV_LEFT); //Follow Line until Intersection, state = NAV_CMD for next action.
//  myGeekBot.lineFollow(NAV_UTURN); //Follow Line until Intersection, state = NAV_CMD for next action.
//  myGeekBot.lineFollow(NAV_RIGHT); //Follow Line until Intersection, state = NAV_CMD for next action.
//  myGeekBot.lineFollow(NAV_STOP); //Follow Line until Intersection, state = NAV_CMD for next action.
//}
//  myGeekBot.timedRotate(1000, 50); // time in mS, rotation speed CCW -100 to CW +100
//  myGeekBot.timedRotate(1000, -50); // time in mS, rotation speed CCW -100 to CW +100
//  myGeekBot.timedDrive(2000, 50); //time in mS, travel speed -100 to 100
//  myGeekBot.timedDrive(2000, -50); //time in mS, travel speed -100 to 100
//  playButtonState = digitalRead(LCD_PLAY_PIN);
//  if (playButtonState == LOW)
//  {

//    myGeekBot.lineFollow(NAV_RIGHT);
//    myGeekBot.lineFollow(NAV_FWD);
//    myGeekBot.lineFollow(NAV_LEFT);
//    myGeekBot.lineFollow(NAV_STOP);
//    myGeekBot.sound(soundDown);
//    myGeekBot.timedDrive(350, 50);
//    delay(3000);
//    myGeekBot.timedDrive(1500, -50);
//    delay(1000);
//    myGeekBot.timedRotate(500, 50);
//    myGeekBot.recoverLine(1); //Follow Line until Intersection, state = NAV_CMD for next action.
//    myGeekBot.lineFollow(NAV_RIGHT);
//    myGeekBot.lineFollow(NAV_FWD);
//    myGeekBot.lineFollow(NAV_FWD);
//    myGeekBot.lineFollow(NAV_STOP);
//  customFunction();
//  }
