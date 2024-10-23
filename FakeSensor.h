class FakeTempSensor {
  public:
    FakeTempSensor(); //: values {4.20,32.0,15.12,7.40,1.0,0,-10,5} {}
    double read();
  private:
    double values[8];
};