#include <M5Stack.h>
#include "M5UnitENV.h"
#include "Sensor.h"
#include "network.h"
#include "ui.h"
#include "plant.h"

const int TOLERANCE_HUMIDITY = 5;
const int TOLERANCE_TEMP = 5;
const int TOLERANCE_LIGHT = 0;

Plant plants[] = {
    Plant("Kaktus", kaktus, 25.0, 30.0, 18.0),
    Plant("Bonsai", bonsai, 22.0, 60.0, 14.00),
    Plant("Orchid", orchid, 21.0, 65.0, 12.00),
    Plant("Agave", agave, 28.0, 40.0, 30.00)
};

int plantCount = 4; //We calculate this at runtime later down the line

Sensory sensory;
Network network;

Plant *selectedPlant;
/*Controller maybe?*/

void compareValues(Sensory &sensory,Plant selectedPlant) {
  SensorValues sv = sensory.read();
  if(sv.currentHumidity < selectedPlant.idealHumidity + TOLERANCE_HUMIDITY && sv.waterLevel == true) {
    //TODO run pump for 5 seconds
  }
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
    //Press for 5 seconds idk
    if(M5.BtnB.pressedFor(5000)) {
        network.update(sensory,500);
    }
    sensory.update();
    updateUI(sensory);
    selectedPlant = &plants[getSelectedPlantIndex()];

    //DEBUG
    Serial.println(selectedPlant->getName());
    //DEBUG

    delay(100);
}
