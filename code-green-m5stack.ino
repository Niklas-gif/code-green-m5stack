#include <M5Stack.h>
#include "FakeSensor.h"
//#include <M5UnitENV.h>

FakeTempSensor fakeSensor = FakeTempSensor();

void hello_world() {
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(4);
  M5.Lcd.setTextColor(GREEN); 
  M5.Lcd.print("CODE GREEN");
}

void setup() {
  M5.begin();
  M5.Power.begin();
  hello_world();
}

void loop() {
  M5.update();
}
