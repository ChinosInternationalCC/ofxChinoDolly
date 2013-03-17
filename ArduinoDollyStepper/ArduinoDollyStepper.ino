/*
 * MotorKnob
 *
 * A stepper motor follows the turns of a potentiometer
 * (or other sensor) on analog input 0.
 *
 * http://www.arduino.cc/en/Reference/Stepper
 * This example code is in the public domain.
 */

#include <Stepper.h>
#include "ChinoDollyComm.h"

// change this to the number of steps on your motor
#define STEPS 255
#define EN_A_PIN 10
#define EN_B_PIN 13

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 8, 9, 11, 12);

// the previous reading from the analog input
int previous = 0;

void setup()
{
  pinMode(EN_A_PIN, OUTPUT);
  pinMode(EN_B_PIN, OUTPUT);  
  digitalWrite(EN_A_PIN, HIGH);
  digitalWrite(EN_B_PIN, HIGH);
  // set the speed of the motor to 30 RPMs
  stepper.setSpeed(100);
  Serial.begin(9600);
}

void serialEvent() {
  while (Serial.available()) {
    int revolutions=0;
    int ReqID=0;
    int NoOfSteps = 0;

    if (Serial.available() >= 2)
    {
        ReqID = Serial.read();
        revolutions = Serial.read();
        if (ReqID == CMD_MOVE_FORWARD)
        {
          #ifdef VERBOSE
          Serial.println(revolutions);
          #endif
          for (int i=0;i < abs(revolutions); i++)
            stepper.step(STEPS);
        }
        else if (ReqID == CMD_MOVE_BACKWARD)
        { 
          #ifdef VERBOSE
          Serial.println(revolutions);
          #endif
          for (int i=0;i < abs(revolutions); i++)
            stepper.step(-STEPS);
        }
        if (ReqID == CMD_SHIFT_LEFT)
        {
          #ifdef VERBOSE
          Serial.println(revolutions);
          #endif
          for (int i=0;i < abs(revolutions); i++)
            stepper.step(STEPS);
        }
        else if (ReqID == CMD_SHIFT_RIGHT)
        { 
          #ifdef VERBOSE
          Serial.println(revolutions);
          #endif
          for (int i=0;i < abs(revolutions); i++)
            stepper.step(-STEPS);
        }
        else if (ReqID == CMD_SET_SPEED)
        { 
          #ifdef VERBOSE
          Serial.println("change speed");
          #endif
          stepper.setSpeed(revolutions);
        }
    }
    
  }
}

void loop()
{

}

