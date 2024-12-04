#include "Sensor.h"

class Network {
  private:
  const char* ssid = "SSID";
  const char* password = "PASSWORD";
  const char* serverUrl = "http://IPADRESSTOCONNECT:8000/data";
  String parseToJson(SensorValues &sv,String &plantName);

  public:
    void init();
    void update(Sensory &sensory);
};