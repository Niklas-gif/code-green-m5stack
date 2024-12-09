#include "Sensor.h"

class Network {
  private:
  const char* ssid = "ssid";
  const char* password = "password";
  const char* serverUrl = "http://adresse:8000/data";
  String parseToJson(SensorValues sv);

  public:
    void init();
    void update(Sensory &sensory);
};