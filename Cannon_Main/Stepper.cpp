#include "Stepper.h"
#include <Arduino.h>

// Stepper Motor X
const int stepPin = 2; //X.STEP
const int dirPin = 5; // X.DIR

void Stepper::begin(void)
{
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
}

void Stepper::ClockWise(int Speed, int duration)
{
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < duration; x++) 
  {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(Speed); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(Speed); 
  }
}
void Stepper::CounterClockWise(int Speed, int duration)
{
  digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < duration; x++) 
  {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(Speed); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(Speed); 
  }
}
