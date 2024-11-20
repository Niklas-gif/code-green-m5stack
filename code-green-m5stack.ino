#include <M5Stack.h>
#include "M5UnitENV.h"
#include "Sensor.h"

struct Plant {
  String name;
  double idealTemprature;
  double idealHumidity;
  int idealLightCondition;
};
Sensory sensory;

void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Power.begin();
  sensory.init();
}

void loop() {
  M5.update();
  sensory.update();
  //DEBUG
  Serial.println(sensory.read().currentHumidity);
  Serial.println(sensory.read().currentTemprature);
  Serial.println(sensory.read().currentLightCondition);
  Serial.println(sensory.read().rawADC);
  Serial.println(sensory.read().waterLevel);
  Serial.println(sensory.isPumpRunning());

  if (M5.BtnB.wasPressed()) {
      sensory.togglePump();
    }
  delay(1000);
  //DEBUG
}
