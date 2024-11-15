
  typedef struct SensorValues {
    double currentTemprature;
    double currentHumidity;
    int currentLightCondition;
  //TODO we store all sensor Values here and use it as as global context
  } SensorValue;

  class Sensor {
    private:
      SensorValues sensorValues;
      bool sht40Init();
      bool bmp280Init();
      
    public:
      SensorValues read();
      void init();
      void update();
  };