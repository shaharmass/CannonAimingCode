/*
cpp code for GY-291 Gyro sensor library
v 1.0.0
by Shahar Mass 
12/09/22
*/
#include "Gyro.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Arduino.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void Gyro::begin(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.begin(115200);
/* Initialise the sensor */
if(!accel.begin())
{
/* There was a problem detecting the ADXL345 ... check your connections */
Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
while(1);
}

/* Set the range to whatever is appropriate for your project */
accel.setRange(ADXL345_RANGE_16_G);
// displaySetRange(ADXL345_RANGE_8_G);
// displaySetRange(ADXL345_RANGE_4_G);
// displaySetRange(ADXL345_RANGE_2_G);
}

double Gyro::GYROX()
{
sensors_event_t event; 
accel.getEvent(&event);
return (event.acceleration.x);//return x axis from sensor
}

double Gyro::GYROY()
{
sensors_event_t event; 
accel.getEvent(&event);
return (event.acceleration.y * 9);//return y axis from sensor
}

double Gyro::GYROZ()
{
sensors_event_t event; 
accel.getEvent(&event);
return (event.acceleration.z * 9);//return z axis from sensor
}
