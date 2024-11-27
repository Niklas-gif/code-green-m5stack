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
    float idealLight;


    Plant(String n, const uint16_t* bmp, float temp, float humidity, float light) {
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
