#include <M5Stack.h>
#include "FakeSensor.h"
//#include <M5UnitENV.h>

// #######################
// # TEST AND FAKE STUFF #
// #######################

FakeTempSensor fakeSensor = FakeTempSensor();
String temp_value;

void fake_init() {
  temp_value = String("temp: ");
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(4);
  M5.Lcd.setTextColor(GREEN); 
  M5.Lcd.print("CODE GREEN");
  delay(2000);
  M5.Lcd.setTextSize(3);
  M5.Lcd.clear();
}

void read_test() {
  M5.Lcd.clear();
  M5.Lcd.setCursor(32,32);
  M5.Lcd.print(temp_value + fakeSensor.read() + "C");
  delay(1000);
}

// #######################
// # TEST AND FAKE STUFF #
// #######################

void setup() {
  M5.begin();
  M5.Power.begin();
  fake_init();
}

void loop() {
  M5.update();
  read_test();
}
