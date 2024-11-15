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

void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Power.begin();
  sensor.init();
}

void loop() {
  M5.update();
  sensor.update();
  //DEBUG
  Serial.println(sensor.read().currentHumidity);
  Serial.println(sensor.read().currentTemprature);
  delay(1000);
  //DEBUG
}
