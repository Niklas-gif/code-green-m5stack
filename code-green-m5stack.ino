#include <M5Stack.h>
#include <M5UnitENV.h>

#include "Sensor.h"
#include "network.h"
#include "ui.h"
#include "plant.h"

//NETWORK ALGORITHMEN
const unsigned long SEND_TRIGGER_TIME = (1000*60)*5;
bool triggerSend = false;
unsigned long currentNetworkTime = 0;
unsigned long previousNetworkTime = 0;
//

//PUMP ALGORITHMEN
const unsigned long PUMP_INTERVAL_TIME = 5000;
bool triggerPump = false;
unsigned long currentPumpTime = 0;
//

const int TOLERANCE_HUMIDITY = 0;
const int TOLERANCE_TEMP = 5;
const int TOLERANCE_LIGHT = 0;

Plant plants[] = {
    Plant("Kaktus", kaktus, 25.0, 45.0, 18.0),
    Plant("Bonsai", bonsai, 22.0, 60.0, 14.00),
    Plant("Orchid", orchid, 21.0, 30.0, 12.00),
    Plant("Agave", agave, 28.0, 40.0, 30.00)
};

int plantCount = 4;

Sensory sensory;
Network network;
Plant *selectedPlant;

void sendData(Sensory &sensory) {
  currentNetworkTime = millis();
  if(currentNetworkTime - previousNetworkTime >= SEND_TRIGGER_TIME) {
    previousNetworkTime = currentNetworkTime;
    network.send(sensory,500);
  }
}

void autoTriggerPump(Sensory &sensory) {
    SensorValues sv = sensory.read();
    if(sv.currentHumidity < selectedPlant->idealHumidity + TOLERANCE_HUMIDITY && sv.waterLevel == true) {
      triggerPump = true;
    } 
    if(triggerPump) {
      if(!sensory.isPumpRunning()) {
        currentPumpTime = millis();
        sensory.togglePump();
      } 

      if(millis() - currentPumpTime >= PUMP_INTERVAL_TIME) {
        triggerPump = false;
        sensory.togglePump();
      } 
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
    autoTriggerPump(sensory);
    sendData(sensory);
    if(M5.BtnB.pressedFor(3000)) {
      network.send(sensory,500);
    }
    sensory.update();
    updateUI(sensory);
    selectedPlant = &plants[getSelectedPlantIndex()];
    delay(100);
}
