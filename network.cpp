#include <WiFi.h>
#include <HTTPClient.h>
#include "network.h"
#include "Sensor.h"

void Network::init() {
   WiFi.begin(ssid, password);

  //TODO stop after 3 trys
  int tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries != 3) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    tries++;
  }
  Serial.println("Connected to WiFi");
}

void Network::update(Sensory &sensor) {
   if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    String jsonData = parseToJson(sensor.read());
    int httpResponseCode = http.POST(jsonData);

    Serial.println("Data sent with response code: " + String(httpResponseCode));
    http.end();
  }
  delay(500);
}

//TOOD {\"sensorValue\": 42}
/*
  typedef struct SensorValues {
    double currentTemprature;
    double currentHumidity;
    int currentLightCondition;
    int rawADC;
    bool waterLevel;
  //TODO we store all sensor Values here and use it as as global context
  } SensorValues;
*/
//"\"currentTemprature\": \"" + String(sv.currentTemprature,2) + "\"\n\"currentHumidity\": \"" + String(sv.currentHumidity) + "\"\n}";
String Network::parseToJson(const SensorValues sv) {
  return "{\"currentTemprature\": \"" + String(sv.currentTemprature,2) + "\",\n\"currentHumidity\": \"" + String(sv.currentHumidity,2) + "\"\n}";
}