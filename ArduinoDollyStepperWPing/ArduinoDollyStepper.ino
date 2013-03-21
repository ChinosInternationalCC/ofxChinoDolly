#include <Stepper.h>
#include <Servo.h> 
#include "ChinoDollyComm.h"

#define STEPS 200
#define STEPS1 255
// change this to fit the number of steps per revolution
// for your motor
// Mercury motor 1.8 degrees per step

#define EN_A 4
#define EN_B 7
#define A_CTRL1 2
#define A_CTRL2 3
#define B_CTRL1 5
#define B_CTRL2 6
#define SERVO   8
#define pingPin 9


// these are the pins connected to the Arduino Motor Shield:                                    
//const int pwmA = 3;
//const int brakeA = 9;
//const int dirA = 12;
//const int pwmB = 11;
//const int brakeB = 8;//this was 8

const int dirB = 13; 
/*
  Initialize the stepper library using the direction pins (dirA and dirB) 
 to control the motor shield. For more details, see the Stepper motor pages, 
 starting with http://arduino.cc/en/Reference/Stepper
 */
//Stepper stepper(STEPS, dirA,dirB); 
bool BckEndReached = false;
bool FwdEndReached = false;

Stepper stepper1(STEPS1, A_CTRL1, A_CTRL2,B_CTRL1,B_CTRL2);
Servo myservo;
int pos = 0;    // variable to store the servo position 
int x = 0;
void setup () {
   pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);  
  digitalWrite(EN_A, LOW);
  digitalWrite(EN_B, LOW);
  // set up all of the pins of the motor shield as outputs:
  //pinMode(pwmA, OUTPUT);
  //pinMode(brakeA, OUTPUT);
  //pinMode(dirA, OUTPUT);  
  //pinMode(pwmB, OUTPUT);
  //pinMode(brakeB, OUTPUT);
  //pinMode(dirB, OUTPUT);

  // set the brake pins LOW to turn them off:
  //digitalWrite(brakeA, LOW);
  //digitalWrite(brakeB, LOW);
  // set the pwm pins HIGH to give maximum power to the motor:
  //digitalWrite(pwmA, HIGH); 
  //digitalWrite(pwmB, HIGH);
  //pinMode(EN_A, OUTPUT);
  //pinMode(EN_B, OUTPUT);  
  //digitalWrite(EN_A, HIGH);
  //digitalWrite(EN_B, HIGH);
  // set the speed at 60 rpm:
  //stepper.setSpeed(50);
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  #if 0
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
 
  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  #endif
  
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
        //for (int i=0;i < abs(revolutions); i++)
        //{
          //checkDistance();
          if (!FwdEndReached)
          {
            enStepper();
            stepper1.step(revolutions);
            disStepper();
          }
        //}
        Serial.write(1);
      }
      else if (ReqID == CMD_MOVE_BACKWARD)
      { 
#ifdef VERBOSE
        Serial.println(revolutions);
#endif
        //for (int i=0;i < abs(revolutions); i++)
        //{
          //checkDistance();
          if (!BckEndReached){
            enStepper();
            stepper1.step(-revolutions);
            disStepper();
          }
        //}
        Serial.write(1);
      }
      if (ReqID == CMD_SHIFT_LEFT)
      {
#ifdef VERBOSE
        Serial.println(revolutions);
#endif
        //disabled for the moment
        //for (int i=0;i < abs(revolutions); i++)
        //{
        //digitalWrite(pwmA, HIGH); 
        //digitalWrite(pwmB, HIGH);
        //stepper.step(revolutions);
        //digitalWrite(pwmA, LOW); 
        //digitalWrite(pwmB, LOW);
        //}
        Serial.write(1);
      }
      else if (ReqID == CMD_SHIFT_RIGHT)
      { 
#ifdef VERBOSE
        Serial.println(revolutions);
#endif
        //disabled for the moment
        //for (int i=0;i < abs(revolutions); i++)
        //{            
        //digitalWrite(pwmA, HIGH); 
        //digitalWrite(pwmB, HIGH);
        //stepper.step(-revolutions);
        //digitalWrite(pwmA, LOW); 
        //digitalWrite(pwmB, LOW);
        //}
        Serial.write(1);
      }
      else if (ReqID == CMD_SET_SPEED)
      { 
#ifdef VERBOSE
        Serial.println("change speed");
#endif
        stepper1.setSpeed(revolutions);
        Serial.write(1);
      }
      else if (ReqID == CMD_TILT_UP)
      { 
        //pos = map(revolutions, 0, 500, 15, 60);
        //pos=revolutions;
        //Serial.println(pos);
        myservo.write(revolutions); 
        Serial.write(1);
      }
      else if (ReqID == CMD_TILT_DOWN)
      { 
        // pos = map(revolutions, 200, 0, 0, 179);                      
        myservo.write(revolutions);              // tell servo to go to position in variable 'pos'         
        Serial.write(1);
        //        }
      }
    }
  }
}
void loop()
{

  

}

void checkDistance(){
 
 // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  if (cm > 260) 
    BckEndReached=true;
  else
    BckEndReached=false;
  if (cm < 10) 
    FwdEndReached=true;
  else
    FwdEndReached=false; 

}
 
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void enStepper(){
 
  digitalWrite(EN_A, HIGH);
  digitalWrite(EN_B, HIGH);
}

void disStepper(){
  
  digitalWrite(EN_A, LOW);
  digitalWrite(EN_B, LOW);
}

