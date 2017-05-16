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
  processSerialCommand();
}

void processSerialCommand()
{
  char buffer[64] = {0};
  int i = 0;

  if ( Serial.available() )
  {
    delay(100); //wait for remaining bytes
    while( Serial.available() && i < sizeof(buffer) )
    {
      buffer[i++] = Serial.read();
    }
    buffer[i++] = '\0';
  }

  if( i > 0 )
  {
    //Compare strings and perform actions
    if (strncmp(buffer, "Matt1", 5) == 0) // Get Matt a Budweiser
    {      
      Beer0(); // Gets Budweiser from Home Position       
      Name0(); // Goes from Beer Fridge to Matt      
    }
    //Compare strings and perform actions
    if (strncmp(buffer, "Rick1", 5) == 0) // Get Matt a Budweiser
    {      
      Beer0(); // Gets Budweiser from Home Position       
      Name1(); // Goes from Beer Fridge to Rick      
    }
    //Compare strings and perform actions
    if (strncmp(buffer, "Kevin1", 6) == 0) // Get Kevin a Budweiser
    {      
      Beer0(); // Gets Budweiser from Home Position       
      Name2(); // Goes from Beer Fridge to Kevin      
    }
    //Compare strings and perform actions
    if (strncmp(buffer, "Wade1", 5) == 0) // Get Wade a Budweiser
    {      
      Beer0(); // Gets Budweiser from Home Position       
      Name3(); // Goes from Beer Fridge to Wade      
    }

    //Compare strings and perform actions
    if (strncmp(buffer, "Matt2", 5) == 0) // Get Matt a Bud Light
    {      
      Beer1(); // Gets Budweiser from Home Position       
      Name0(); // Goes from Beer Fridge to Matt      
    }
    //Compare strings and perform actions
    if (strncmp(buffer, "Rick2", 5) == 0) // Get Matt a Bud Light
    {      
      Beer1(); // Gets Budweiser from Home Position       
      Name1(); // Goes from Beer Fridge to Rick      
    }
    //Compare strings and perform actions
    if (strncmp(buffer, "Kevin2", 6) == 0) // Get Kevin a Bud Light
    {      
      Beer1(); // Gets Budweiser from Home Position       
      Name2(); // Goes from Beer Fridge to Kevin      
    }
    //Compare strings and perform actions
    if (strncmp(buffer, "Wade2", 5) == 0) // Get Wade a Bud Light
    {      
      Beer1(); // Gets Budweiser from Home Position       
      Name3(); // Goes from Beer Fridge to Wade      
    }

    //Compare strings and perform actions
    if (strncmp(buffer, "Matt3", 5) == 0) // Get Matt a Rolling Rock
    {      
      Beer1(); // Gets Budweiser from Home Position       
      Name0(); // Goes from Beer Fridge to Matt      
    }
    //Compare strings and perform actions
    if (strncmp(buffer, "Rick3", 5) == 0) // Get Matt a Rolling Rock
    {      
      Beer1(); // Gets Budweiser from Home Position       
      Name1(); // Goes from Beer Fridge to Rick      
    }
    //Compare strings and perform actions
    if (strncmp(buffer, "Kevin3", 6) == 0) // Get Kevin a Rolling Rock
    {      
      Beer1(); // Gets Budweiser from Home Position       
      Name2(); // Goes from Beer Fridge to Kevin      
    }
    //Compare strings and perform actions
    if (strncmp(buffer, "Wade3", 5) == 0) // Get Wade a Rolling Rock
    {
      Beer1(); // Gets Budweiser from Home Position 
      Name3(); // Goes from Beer Fridge to Wade      
    }

  }
  
}

// Start Command list

void Beer0() // Get Budweiser
{
  myGeekBot.sound(soundWhistle);
  myGeekBot.lineFollow(NAV_UTURN); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_LEFT); //Follow Line until Intersection, state = NAV_CMD for next action.
  getBeer();
  myGeekBot.lineFollow(NAV_LEFT);
}

void Beer1() // Get Bud Light
{
  myGeekBot.sound(soundWhistle);
  myGeekBot.lineFollow(NAV_UTURN); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_LEFT); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  getBeer();
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_LEFT);
}

void Beer2() // Get Rolling Rock
{
  myGeekBot.sound(soundWhistle);
  myGeekBot.lineFollow(NAV_UTURN); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_LEFT); //Follow Line until Intersection, state = NAV_CMD for next action.
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
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
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
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
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
  myGeekBot.lineFollow(NAV_FWD); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_STOP); //Follow Line until Intersection, state = NAV_CMD for next action.
}

void getBeer() // Motions for getting a beer
{
  myGeekBot.lineFollow(NAV_LEFT); //Follow Line until Intersection, state = NAV_CMD for next action.
  myGeekBot.lineFollow(NAV_STOP);
  myGeekBot.sound(soundDown);
  myGeekBot.timedDrive(350, 50);
  delay(3000);
  myGeekBot.timedDrive(1500, -30);
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
  myGeekBot.timedRotate(500, 50);
  myGeekBot.recoverLine(1); //Follow Line until Intersection, state = NAV_CMD for next action.
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
