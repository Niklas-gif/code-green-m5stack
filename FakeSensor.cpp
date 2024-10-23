#include <cstdio>
#include <Arduino.h>
#include "FakeSensor.h"



FakeTempSensor::FakeTempSensor() {
    values[0] = 4.20;
    values[1] = 32.0;
    values[2] = 15.12;
    values[3] = 7.40;
    values[4] = 1.0;
    values[5] = 0;
    values[6] = -10;
    values[7] = 5;

    randomSeed(analogRead(0));  
}

double FakeTempSensor::read() {
  
  return FakeTempSensor::values[random(0,7)];
}