#include <M5Stack.h>
//#include <M5UnitENV.h>


void setup() {
  M5.begin();
  M5.Power.begin();
}

void loop() {
  M5.update();
}
