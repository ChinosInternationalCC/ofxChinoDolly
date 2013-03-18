//https://github.com/zevenwolf/Motor-Shield

#include <Stepper.h>
#include <Servo.h> 
#include "ChinoDollyComm.h"

#define STEPS 200
#define STEPS1 255
// change this to fit the number of steps per revolution
  // for your motor
// Mercury motor 1.8 degrees per step

//#define EN_A 2
//#define EN_B 6
#define A_CTRL1 4
#define A_CTRL2 5
#define B_CTRL1 6
#define B_CTRL2 7
#define SERVO 2


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
Stepper stepper1(STEPS1, A_CTRL1, A_CTRL2,B_CTRL1,B_CTRL2);
Servo myservo;
int pos = 0;    // variable to store the servo position 
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
  //pinMode(EN_A, OUTPUT);
  //pinMode(EN_B, OUTPUT);  
  //digitalWrite(EN_A, HIGH);
  //digitalWrite(EN_B, HIGH);
  // set the speed at 60 rpm:
  stepper.setSpeed(50);
  stepper1.setSpeed(100);
   myservo.attach(SERVO);
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
            stepper1.step(STEPS1);
           }
        }
        else if (ReqID == CMD_MOVE_BACKWARD)
        { 
          #ifdef VERBOSE
          Serial.println(revolutions);
          #endif
          for (int i=0;i < abs(revolutions); i++)
          {
            stepper1.step(-STEPS1);
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
        else if (ReqID == CMD_TILT_UP)
        { 
          for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
          {                                  // in steps of 1 degree 
                myservo.write(pos);              // tell servo to go to position in variable 'pos' 
                  delay(15);                       // waits 15ms for the servo to reach the position 
          } 
        }
        else if (ReqID == CMD_TILT_DOWN)
        { 
          for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
            {                                
            myservo.write(pos);              // tell servo to go to position in variable 'pos' 
              delay(15);                       // waits 15ms for the servo to reach the position 
          } 
        }
    }
    
  }
}
void loop () {
}
