#include <WiFi.h>
#include <HTTPClient.h>
#include "network.h"
#include "Sensor.h"

void Network::init() {
   WiFi.begin(ssid, password);

  //TODO stop after 3 trys
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void Network::update(Sensory &sensor) {
   if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    String jsonData = "{\"sensorValue\": 42}";
    int httpResponseCode = http.POST(jsonData);

    Serial.println("Data sent with response code: " + String(httpResponseCode));
    http.end();
  }
  delay(2000);
}

//TOOD
String Network::parseToJson(SensorValues &sv,String &plantName) {
  return " ";
}