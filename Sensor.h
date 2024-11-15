
  typedef struct SensorValues {
    double currentTemprature;
    double currentHumidity;
    int currentLightCondition;
  //TODO we store all sensor Values here and use it as as global context
  } SensorValue;

  class Sensory {
    private:
      SensorValues sensorValues;
      bool pumpIsRunning;
      bool sht40Init();
      bool bmp280Init();
      bool pumpInit();
      
    public:
      void init();
      void update();
      void togglePump();
      bool isPumpRunning();
      SensorValues read();
  };