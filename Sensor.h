
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
      bool waterLevelSensorInit();
      bool sht40Init();
      bool bmp280Init();
      bool pumpInit();
      bool lightSensorInit();
      
    public:
      void init();
      void update();
      void togglePump();
      bool isPumpRunning();
      SensorValues read();
  };