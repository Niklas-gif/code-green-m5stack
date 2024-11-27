#pragma once

  
  typedef struct SensorValues {
    double currentTemprature;
    double currentHumidity;
    int currentLightCondition;
    int rawADC;
    bool waterLevel;
  //TODO we store all sensor Values here and use it as as global context
  } SensorValues;

  class Sensory {
    private:
      SensorValues sensorValues;
      bool pumpIsRunning;
      bool waterLevelLED;
      bool waterLevelSensorInit();
      bool sht40Init();
      bool bmp280Init();
      bool pumpInit();
      bool lightSensorInit();
      
    public:
      void init();
      void update();
      void togglePump();
      void toggleWaterLevelLED();
      bool isPumpRunning();
      SensorValues read();
  };