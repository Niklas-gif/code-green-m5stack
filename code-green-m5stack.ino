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

int plantCount = 4; //We calculate this at runtime later down the line

Sensory sensory;
NetworkHelper network;

Plant *selectedPlant;
/*Controller maybe?*/

void compareValues(SensorValues sensorValues,Plant selectedPlant) {

}

void setup() {
    Serial.begin(115200);
    M5.begin();
    M5.Power.begin();
    selectedPlant = &plants[0];
    sensory.init();
    initializeUI(sensory);
    network.init();
}

void loop() {
    M5.update();
    sensory.update();
    updateUI(sensory);
    selectedPlant = &plants[getSelectedPlantIndex()];

    //DEBUG
    /*Serial.println(sensory.read().currentHumidity);
    Serial.println(sensory.read().currentTemprature);
    Serial.println(sensory.read().currentLightCondition);
    Serial.println(sensory.read().rawADC);
    Serial.println(sensory.read().waterLevel);
    Serial.println(sensory.isPumpRunning());*/
    //Serial.println(selectedPlant->getName());
    Serial.println(selectedPlant->getName());
    //DEBUG
    network.update();

    delay(100);
}
