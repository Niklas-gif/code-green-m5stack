#include <cstdio>
#include "FakeSensor.h"

/*class FakeTempSensor {
  public:
    void read() {}
}*/

float FakeTempSensor::read() {
  return 42.0;
}