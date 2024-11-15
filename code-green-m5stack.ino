#include <M5Stack.h>
#include <Wire.h>
#include <Digital_Light_TSL2561.h>
#include "M5UnitENV.h"
#include "Sensor.h"

struct Plant {
  String name;
  double idealTemprature;
  double idealHumidity;
  int idealLightCondition;
};

Sensor sensor;

/*// PINS PUMP 
#define INPUT_PIN 36 
#define PUMP_PIN  26

 //PINS TEMP SENSOR 
#define TEMP_SDA_PIN 21
#define TEMP_SCL_PIN 22


 //heat humidity sensor
SHT4X sht4; 
BMP280 bmp;*/


void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Power.begin();
  sensor.init();
}

void loop() {
  M5.update();
  //Serial.print(sensor.sensorValues.idealHumidity);
}
