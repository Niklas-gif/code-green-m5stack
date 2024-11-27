#include <M5Stack.h>
#include "M5UnitENV.h"
#include "Sensor.h"
#include "ui.h"
#include "plant.h"

Plant plants[] = {
    Plant("Kaktus", kaktus, 25.0, 30.0, 18.0),
    Plant("Bonsai", bonsai, 22.0, 60.0, 14.00),
    Plant("Orchid", orchid, 21.0, 65.0, 12.00),
    Plant("Agave", agave, 28.0, 40.0, 30.00)
};

Sensory sensory;

void setup() {
    Serial.begin(115200);
    M5.begin();
    M5.Power.begin();
    sensory.init();
    initializeUI(sensory);
}

void loop() {
    M5.update();
    sensory.update();
    updateUI(sensory);
    

    //DEBUG
    /*Serial.println(sensory.read().currentHumidity);
    Serial.println(sensory.read().currentTemprature);
    Serial.println(sensory.read().currentLightCondition);
    Serial.println(sensory.read().rawADC);
    Serial.println(sensory.read().waterLevel);
    Serial.println(sensory.isPumpRunning());*/
    //DEBUG

    delay(100);
}
