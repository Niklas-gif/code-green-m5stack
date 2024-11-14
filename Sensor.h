
//namespace GlobalSensor {

  typedef struct SensorValues {
    double idealTemprature;
    double idealHumidity;
    int idealLightCondition;
  //TODO we store all sensor Values here and use it as as global context
  } SensorValue;

  class Sensor {
    public:
      SensorValues sensorValues;
      void init();
      void update();
  };
//}