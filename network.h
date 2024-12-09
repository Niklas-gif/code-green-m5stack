#include "Sensor.h"
//#include "passwd.h"

class Network {
  private:
  const char* ssid = "";
  const char* password = "";
  const char* serverUrl = "";
  String parseToJson(SensorValues sv);

  public:
    void init();
    void update(Sensory &sensory);
};