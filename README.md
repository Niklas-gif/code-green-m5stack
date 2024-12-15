# code-green-m5stack

## How to use

### Inital setup
You have to create a headerfile passwd.h
```bash
#ifndef PASSWD_H
#define PASSWD_H

constexpr const char* SSID = "ssid";
constexpr const char* PASSWORD = "password";
constexpr const char* SERVERURL = "http://adresse:port/data";

#endif
```

Or comment out passwd.h inside network.h and replace the constants

```bash
#pragma once

#include "Sensor.h"
//#include "passwd.h"
#include <WiFiType.h>

class Network {
  private:
  const char* ssid = "";
  const char* password = "";
  const char* serverUrl = "";
  String parseToJson(SensorValues sv);

  public:
    void init();
    void send(Sensory &sensory, int delayTime);
    wl_status_t status();
};
```

### Modules & PINS
The input pins are defined inside Sensor.cpp
```bash
/* PINS PUMP */
#define INPUT_PIN 36 
#define PUMP_PIN  26

/* PINS TEMP SENSOR */
#define TEMP_SDA_PIN 21
#define TEMP_SCL_PIN 22

/* PINS WATERLEVEL SENSOR*/
#define WATERLEVEL_OUT_PIN 5
#define WATERLEVEL_LED_PIN 2 

/* heat humidity sensor*/
SHT4X sht40; 
BMP280 bmp;
```




