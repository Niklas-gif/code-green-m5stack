#include <Arduino.h>
#include <M5Stack.h>
#include <Wire.h>
#include <Digital_Light_TSL2561.h>
#include <M5UnitENV.h> 
#include "Sensor.h"


/* PINS PUMP */
#define INPUT_PIN 36 
#define PUMP_PIN  26

/* PINS TEMP SENSOR */
#define TEMP_SDA_PIN 21
#define TEMP_SCL_PIN 22

/* PINS WATERLEVEL SENSOR*/
#define WATERLEVEL_OUT_PIN 5

/* heat humidity sensor*/
SHT4X sht40; 
BMP280 bmp;

bool Sensory::waterLevelSensorInit() {
  pinMode(WATERLEVEL_OUT_PIN, INPUT);
  return true;
}

bool Sensory::sht40Init() {
  if (!sht40.begin(&Wire, SHT40_I2C_ADDR_44)) {
       Serial.println("Couldn't find SHT4x");
      return false;
  }

  sht40.setPrecision(SHT4X_HIGH_PRECISION);
  sht40.setHeater(SHT4X_NO_HEATER);
  return true;
}

bool Sensory::bmp280Init() {
      if (!bmp.begin(&Wire, BMP280_I2C_ADDR)) {
        Serial.println("Couldn't find BMP280");
        return false;
    }
    /* Default settings from datasheet. */
    bmp.setSampling(BMP280::MODE_NORMAL,     /* Operating Mode. */
                    BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    BMP280::FILTER_X16,      /* Filtering. */
                    BMP280::STANDBY_MS_500); /* Standby time. */
    return true;
}

bool Sensory::lightSensorInit() {
  TSL2561.init();
  return true;
}

bool Sensory::pumpInit() {
    pinMode(INPUT_PIN, INPUT);
    pinMode(PUMP_PIN, OUTPUT);
    pumpIsRunning = false;
  return true;
}


void Sensory::init() {
  /*if(sht40Init() && bmp280Init()) {
    Serial.println("Okay");
  } else {
    Serial.println("Failed to Init sensor");
  }*/
  waterLevelSensorInit();
  sht40Init();
  bmp280Init();
  lightSensorInit();
  pumpInit();
}

void Sensory::update() {
  if(sht40.update()) {
    Sensory::sensorValues.currentHumidity = sht40.humidity;
  }

  if(bmp.update()) {
    Sensory::sensorValues.currentTemprature = sht40.cTemp;
  }
  Sensory::sensorValues.currentLightCondition = TSL2561.readFSpecLuminosity();

  Sensory::sensorValues.rawADC = analogRead(INPUT_PIN);

  Sensory::sensorValues.waterLevel = digitalRead(WATERLEVEL_OUT_PIN);
}

//Sensor values are read only!
SensorValues Sensory::read() {
  return Sensory::sensorValues;
}

void Sensory::togglePump() {
  pumpIsRunning = !pumpIsRunning;
  digitalWrite(PUMP_PIN, pumpIsRunning);
}

bool Sensory::isPumpRunning() {
  return pumpIsRunning;
}