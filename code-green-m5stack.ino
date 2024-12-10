#include <M5Stack.h>
#include <M5UnitENV.h>

#include "Sensor.h"
#include "network.h"
#include "ui.h"
#include "plant.h"

unsigned long previousTime = 0;

//SAVE ALGORITHMEN
const unsigned long SAVE_TRIGGER_TIME = (1000*60)*5;
bool triggerSave = true;
unsigned long currentSaveTime = 0;
//

//NETWORK ALGORITHMEN
const unsigned long SEND_TRIGGER_TIME = (1000*60)*10;
bool triggerRequest = false;
unsigned long currentNetworkTime = 0;
//

//PUMP ALGORITHMEN
const unsigned long PUMP_INTERVAL_TIME = 5000; //LATER 10 seconds
bool triggerPump = false;
unsigned long currentPumpTime = 0;
//

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

void triggerPumpBackground() {
  //if(sv.currentHumidity < selectedPlant.idealHumidity + TOLERANCE_HUMIDITY && sv.waterLevel == true) {} <- CONDITION
  if(!sensory.isPumpRunning()) {
    currentPumpTime = millis();
    sensory.togglePump();
  } 

  if(millis() - currentPumpTime >= PUMP_INTERVAL_TIME) {
    triggerPump = false;
    sensory.togglePump();
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
    //unsigned long currentTime = millis();
    M5.update();

    if(M5.BtnA.pressedFor(1000)) {
      triggerPump = true;
    } 
    if(triggerPump) {
      triggerPumpBackground();
    }

    if(M5.BtnB.pressedFor(3000)) {
        network.update(sensory,500);
    }
    sensory.update();
    updateUI(sensory);
    selectedPlant = &plants[getSelectedPlantIndex()];
    //previousTime = currentTime;
    delay(100);
}
