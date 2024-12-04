#include <WiFi.h>
#include <HTTPClient.h>
#include "network.h"

void Network::init() {
   WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void Network::update() {
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