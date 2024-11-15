
  typedef struct SensorValues {
    double idealTemprature;
    double idealHumidity;
    int idealLightCondition;
  //TODO we store all sensor Values here and use it as as global context
  } SensorValue;

  class Sensor {
    private:
      bool sht40Init();
      bool bmp280Init();
      
    public:
      SensorValues sensorValues;
      void init();
      void update();
  };