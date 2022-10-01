//libraris
#include "Gyro.h"
#include "Ultrasonic.h"
#include "Stepper.h"
//testing const
#define NUMBER_OF_TESTS 10
#define NUMBER_OF_STEPS 5
#define STEPPER_SPEED 1000
//routine const
#define LED_PIN 13//the pin of the led that indicates if an object is out of range
#define GYRO_OFFSET 0.1//the accurecy value of the gyro(if the change is lower or equal to this value dont change the cannon position)
//objects params
Stepper stepper;
Gyro gyro;
Ultrasonic ultrasonic;

//testing params
int numberOfSteps;
double gyroX;
double prevGyroX;
double gyroAver;

//routine params
int ultraDistance;//the input distance from the ultra sonic sensor
double currGyroX;//the curr gyro x value
double wantedGyroX;//the wanted gyro x value based on the distance from target

void setup() 
{
  
  numberOfSteps = 0;
  gyroAver = 0;

  //setup functions
  gyro.begin();
  ultrasonic.begin();
  stepper.begin();

  pinMode(LED_PIN , OUTPUT);//set the led pin to output
  
}

void loop() 
{
  delay(100);//do a delay before every loop
  
  //print the curr gyro x and the distance
  Serial.print("the curr gyro x: ");
  Serial.println(gyro.GYROX());
  Serial.print("distance: ");
  Serial.println(ultrasonic.Distance());
  
  //set ultra distance and curr gyro x to the curr distance and gyro x
  ultraDistance = ultrasonic.Distance();
  currGyroX = gyro.GYROX();
  
  if(ultrasonic.Distance() < 100){//if the ultra sonic detects an object
    digitalWrite(LED_PIN , LOW);//turn the led off if object is in range
    if(currGyroX < 0){//if the gyro is too low (less then 0)
      stepper.ClockWise(STEPPER_SPEED,NUMBER_OF_STEPS);//do one step clock wise
    }
    else{
      wantedGyroX = ultraDistance/20.0;//calculate the wanted gyro x
      Serial.print("wanted gyro x: ");
      Serial.println(wantedGyroX);
      if(wantedGyroX > 5){//if the wanted gyro x is bigger then 5 (45 degrees) deacrese it back to 5
        wantedGyroX = 5;
      }
    
      if((wantedGyroX > currGyroX)&&((wantedGyroX - currGyroX) >= GYRO_OFFSET)){//if the wanted gyro x is bigger then the curr gyro x
        stepper.ClockWise(STEPPER_SPEED,NUMBER_OF_STEPS);//do one step clock wise
      }

      if((wantedGyroX < currGyroX)&&((currGyroX - wantedGyroX) >= (-1 * GYRO_OFFSET))){//if the wanted gyro x is smaller then the curr gyro x
        stepper.CounterClockWise(STEPPER_SPEED,NUMBER_OF_STEPS);//do one step clock wise
      }
    }
    
  }
  else{//if the curr object is out of range
    digitalWrite(LED_PIN , HIGH);//if the object is unrecheble set the led on
  }
  
}
