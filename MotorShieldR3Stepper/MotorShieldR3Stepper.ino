#include <Stepper.h>

#define STEPS 200
//const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
  // for your motor
// Mercury motor 1.8 degrees per step


// initialize the stepper library on the motor shield
Stepper stepper(STEPS, 12,13);    


// give the motor control pins names:
const int pwmA = 3;
const int pwmB = 11;
const int brakeA = 9;
const int brakeB = 8;
//const int dirA = 12;
//const int dirB = 13;

int x = 0;
void setup () {
Serial.begin(9600);
// set the PWM and brake pins so that the direction pins  // can be used to control the motor:
pinMode(pwmA, OUTPUT);
pinMode(pwmB, OUTPUT);
pinMode(brakeA, OUTPUT);
pinMode(brakeB, OUTPUT);
digitalWrite(pwmA, HIGH);
digitalWrite(pwmB, HIGH);
digitalWrite(brakeA, LOW);
digitalWrite(brakeB, LOW);

// initialize the serial port:
Serial.begin(9600);
// set the motor speed (for multiple steps only):
stepper.setSpeed(100);

} 
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    //char inChar = (char)Serial.read(); 
    int revolutions=0;
    int dir=0;
    int NoOfSteps = 0;
    // add it to the inputString:
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    //if (inChar == 'f') {
    //  stepper.step(STEPS);
    //} 
    //if (inChar == 'b') {
    //  stepper.step(-STEPS);
    //}
    //val = Serial.parseInt();
    if (Serial.available() >= 2)
    {
        dir = Serial.read();
        revolutions = Serial.read();
        if (dir == 0)
        {
          Serial.println(revolutions);
          for (int i=0;i < abs(revolutions); i++)
            stepper.step(STEPS);
        }
        else
        { 
          Serial.println(revolutions);
          for (int i=0;i < abs(revolutions); i++)
            stepper.step(-STEPS);
        }
    }
    
  }
}
void loop () {

  //myStepper.step(3600);
  //myStepper.step(-3600);

  //delay(2000);
}
