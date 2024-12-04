#include <M5Stack.h>
#include "M5UnitENV.h"
#include "Sensor.h"
#include "ui.h"
#include "plant.h"
#include <EEPROM.h>

#define EEPROM_SIZE 512

Plant plants[] = {
    Plant("Kaktus", kaktus, 25.0, 30.0, 18.0),
    Plant("Bonsai", bonsai, 22.0, 60.0, 14.00),
    Plant("Orchid", orchid, 21.0, 65.0, 12.00),
    Plant("Agave", agave, 28.0, 40.0, 30.00)
};

int plantCount = 4; 

Sensory sensory;

Plant *selectedPlant;

struct SensorValue {
    float currentHumidity;
    float currentTemprature;
};

int eeAddress = 0; 

/* void compareValues(SensorValues sensorValues, Plant selectedPlant) {
}
*/

void setup() {
    Serial.begin(115200);
    M5.begin();
    M5.Power.begin();

    // EEPROM initialisieren
    if (!EEPROM.begin(EEPROM_SIZE)) {
        Serial.println("Failed to initialize EEPROM");
        return;
    }

    selectedPlant = &plants[0];
    sensory.init();
    initializeUI(sensory);

    // Sensordaten auslesen und speichern
    SensorValues values = sensory.read();
    EEPROM.put(eeAddress, values); 
    EEPROM.commit();
    Serial.println("Written SensorValues to EEPROM");

    //Werte aus EEPROM lesen
    SensorValues storedValues;
    EEPROM.get(eeAddress, storedValues); // Werte auslesen
    Serial.println("Read SensorValues from EEPROM:");
    Serial.print("Temperature: ");
    Serial.println(storedValues.currentTemprature);
    Serial.print("Humidity: ");
    Serial.println(storedValues.currentHumidity);
}

void loop() {
    M5.update();
    sensory.update();
    updateUI(sensory);
    selectedPlant = &plants[getSelectedPlantIndex()];

    SensorValues storedValues;
    EEPROM.get(eeAddress, storedValues);

    Serial.println("Reading SensorValues in loop:");
    Serial.print("Temperature: ");
    Serial.println(storedValues.currentTemprature);
    Serial.print("Humidity: ");
    Serial.println(storedValues.currentHumidity);

    delay(5000); 
}
