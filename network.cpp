#include <WiFi.h>
#include <HTTPClient.h>
#include "network.h"
#include "Sensor.h"

void Network::init() {
  WiFi.begin(ssid, password);
  int tries = 0;

  while (WiFi.status() != WL_CONNECTED && tries != 3) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    tries++;
  }
  if(WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to WiFi");
    return;
  }

  return;
}

void Network::send(Sensory &sensor,int delayTime) {
   if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    String jsonData = parseToJson(sensor.read());
    int httpResponseCode = http.POST(jsonData);

    Serial.println("Data sent with response code: " + String(httpResponseCode));
    http.end();
  }
  delay(delayTime);
}

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
//TODO plant name rest of the values
String Network::parseToJson(const SensorValues sv) {
  return "{\"currentTemprature\": \"" + String(sv.currentTemprature,2) + "\",\n\"currentHumidity\": \"" + String(sv.currentHumidity,2) + "\"\n}";
}

bool Network::status() {
  if(WiFi.status() == WL_CONNECTED) {
    return true;
  }
  return false;
}
