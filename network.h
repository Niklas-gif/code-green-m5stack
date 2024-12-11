#include "Sensor.h"
#include "passwd.h"

class Network {
  private:
  const char* ssid = SSID;
  const char* password = PASSWORD;
  const char* serverUrl = SERVERURL;
  String parseToJson(SensorValues sv);

  public:
    void init();
    void send(Sensory &sensory, int delayTime);
};