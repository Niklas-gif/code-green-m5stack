#include <Arduino.h>
#include <M5Stack.h>
#include <Wire.h>
#include <Digital_Light_TSL2561.h>
#include <M5UnitENV.h> 
#include "Sensor.h"

//using namespace GlobalSensor;

/* PINS PUMP */
#define INPUT_PIN 36 
#define PUMP_PIN  26

/* PINS TEMP SENSOR */
#define TEMP_SDA_PIN 21
#define TEMP_SCL_PIN 22

/* heat humidity sensor*/
SHT4X sht4; 
BMP280 bmp;

void Sensor::init() {

}

void Sensor::update() {
  Sensor::sensorValues.idealHumidity = 42;
}