#ifndef PLANT_H
#define PLANT_H

#include <M5Stack.h>
#include "picture.h"

typedef struct PlantRaw {
  String name;
  double idealTemperature;
  double idealHumidity;
  //TODO mehr werte vielleicht?

} PlantRaw;

class Plant {
private:
      String name;
public:
    const uint16_t* bitmap;  
    double idealTemperature;
    double idealHumidity;
    int idealLight;

    Plant(String n, const uint16_t* bmp, double temp, double humidity, double light) {
        name = n;
        bitmap = bmp;
        idealTemperature = temp;
        idealHumidity = humidity;
        idealLight = light; 
    }

    String getName() const {
        return name;
    }
};

#endif
