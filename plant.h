#ifndef PLANT_H
#define PLANT_H

#include <M5Stack.h>
#include "picture.h" 

class Plant {
public:
    String name;
    const uint16_t* bitmap;  
    float idealTemperature;
    float idealHumidity;

    Plant(String n, const uint16_t* bmp, float temp, float humidity) {
        name = n;
        bitmap = bmp;
        idealTemperature = temp;
        idealHumidity = humidity;
    }

    String getName() const {
        return name;
    }
};

#endif
