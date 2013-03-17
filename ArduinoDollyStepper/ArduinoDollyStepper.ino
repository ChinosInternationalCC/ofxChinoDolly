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
void loop()
{
  // get the sensor value
  //int val = analogRead(0);

  // move a number of steps equal to the change in the
  // sensor reading
  //stepper.step(STEPS);
  //delay(300);
  //stepper.step(-STEPS);
  //stepper.step(val - previous);
  // remember the previous value of the sensor
  //previous = val;
}

