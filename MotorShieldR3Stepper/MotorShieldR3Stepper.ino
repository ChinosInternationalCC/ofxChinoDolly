//https://github.com/zevenwolf/Motor-Shield

#include <Stepper.h>
#include "ChinoDollyComm.h"

#define STEPS 200
// change this to fit the number of steps per revolution
  // for your motor
// Mercury motor 1.8 degrees per step


// these are the pins connected to the Arduino Motor Shield:                                    
const int pwmA = 3;
const int brakeA = 9;
const int dirA = 12;
const int pwmB = 11;
const int brakeB = 8;
const int dirB = 13; 
/*
  Initialize the stepper library using the direction pins (dirA and dirB) 
 to control the motor shield. For more details, see the Stepper motor pages, 
 starting with http://arduino.cc/en/Reference/Stepper
 */
Stepper stepper(STEPS, dirA,dirB);  

int x = 0;
void setup () {
  // set up all of the pins of the motor shield as outputs:
  pinMode(pwmA, OUTPUT);
  pinMode(brakeA, OUTPUT);
  pinMode(dirA, OUTPUT);  
  pinMode(pwmB, OUTPUT);
  pinMode(brakeB, OUTPUT);
  pinMode(dirB, OUTPUT);

  // set the brake pins LOW to turn them off:
  digitalWrite(brakeA, LOW);
  digitalWrite(brakeB, LOW);
  // set the pwm pins HIGH to give maximum power to the motor:
  //digitalWrite(pwmA, HIGH); 
  //digitalWrite(pwmB, HIGH);

  // set the speed at 60 rpm:
  stepper.setSpeed(60);

  // initialize the serial port:
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
          {
            digitalWrite(pwmA, HIGH); 
            digitalWrite(pwmB, HIGH);
            stepper.step(STEPS);
            digitalWrite(pwmA, LOW); 
            digitalWrite(pwmB, LOW);
          }
        }
        else if (ReqID == CMD_MOVE_BACKWARD)
        { 
          #ifdef VERBOSE
          Serial.println(revolutions);
          #endif
          for (int i=0;i < abs(revolutions); i++)
          {
            digitalWrite(pwmA, HIGH); 
            digitalWrite(pwmB, HIGH);
            stepper.step(-STEPS);
            digitalWrite(pwmA, LOW); 
            digitalWrite(pwmB, LOW);
          }
        }
        if (ReqID == CMD_SHIFT_LEFT)
        {
          #ifdef VERBOSE
          Serial.println(revolutions);
          #endif
          for (int i=0;i < abs(revolutions); i++)
          {
            digitalWrite(pwmA, HIGH); 
            digitalWrite(pwmB, HIGH);
            stepper.step(STEPS);
            digitalWrite(pwmA, LOW); 
            digitalWrite(pwmB, LOW);
          }
        }
        else if (ReqID == CMD_SHIFT_RIGHT)
        { 
          #ifdef VERBOSE
          Serial.println(revolutions);
          #endif
          for (int i=0;i < abs(revolutions); i++)
          {            
            digitalWrite(pwmA, HIGH); 
            digitalWrite(pwmB, HIGH);
            stepper.step(-STEPS);
            digitalWrite(pwmA, LOW); 
            digitalWrite(pwmB, LOW);
          }
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
void loop () {
}
