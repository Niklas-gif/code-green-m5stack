#ifndef PLANT_H
#define PLANT_H

#include <M5Stack.h>
#include "picture.h"

class Plant {
private:
      String name;
public:
    const uint16_t* bitmap;  
    double idealTemperature;
    double idealHumidity;
    int idealLight;

    Plant(String n, const uint16_t* bmp, double temp, double humidity, int light) {
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
