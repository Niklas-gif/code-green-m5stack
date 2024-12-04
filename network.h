class Network {
  private:
  const char* ssid = "SSID";
  const char* password = "PASSWORD";
  const char* serverUrl = "http://IPADRESSTOCONNECT:8000/data";

  public:
    void init();
    String parseToJson();
    void update();
};