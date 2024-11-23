#include <M5Stack.h>
#include "M5UnitENV.h"
#include "Sensor.h"
#include "ui.h"
#include "input.h"

struct Plant {
    String name;
    double idealTemperature;
    double idealHumidity;
    int idealLightCondition;
};

Plant plants[] = {
    {"Cactus", 30.0, 10.0, 200},
    {"Bonsai", 22.0, 50.0, 300},
    {"Orchid", 25.0, 60.0, 250},
    {"Agave", 30.0, 30.0, 180}
};

const int totalPlants = sizeof(plants) / sizeof(plants[0]);
int selectedPlantIndex = 0;

Sensory sensory;

void setup() {
    Serial.begin(115200);
    M5.begin();
    M5.Power.begin();

    sensory.init();
    initializeUI();
}

void loop() {
    M5.update();
    sensory.update();
    updateUI();
    processUserInput();

    //DEBUG
    Serial.println(sensory.read().currentHumidity);
    Serial.println(sensory.read().currentTemprature);
    Serial.println(sensory.read().currentLightCondition);
    Serial.println(sensory.read().rawADC);
    Serial.println(sensory.read().waterLevel);
    Serial.println(sensory.isPumpRunning());
    //DEBUG

    delay(100);
}
