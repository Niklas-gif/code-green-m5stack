#include <M5Stack.h>
#include "FakeSensor.h"
//#include <M5UnitENV.h>

// #######################
// # TEST AND FAKE STUFF #
// #######################

FakeTempSensor fakeSensor = FakeTempSensor();
String temp_value;
int counter;
SemaphoreHandle_t counterMutex;

void fake_init() {
  temp_value = String("temp: ");
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(4);
  M5.Lcd.setTextColor(GREEN); 
  M5.Lcd.print("CODE GREEN");
  delay(2000);
  M5.Lcd.setTextSize(3);
  M5.Lcd.clear();
}

void read_test() {
  M5.Lcd.clear();
  M5.Lcd.setCursor(32,32);
  M5.Lcd.print(temp_value + fakeSensor.read() + "C");
  delay(1000);
}

// #######################
// # TEST AND FAKE STUFF #
// #######################


void task1(void* pvParameters) { 
    while (1) {
      counter++;
      //delay(1000);
      vTaskDelay(1000 / portTICK_PERIOD_MS); 
    }
}

void task2(void* pvParameters) { 
    while (1) {  
      M5.update();
      read_test();
      M5.lcd.setCursor(64,64);
      M5.lcd.print("Counter" + counter);
      //delay(1000); 
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void setup() {
  M5.begin();
  M5.Power.begin();
  fake_init();
  //xTaskCreatePinnedToCore(task1, "task1", 4096, NULL, 1, NULL, 0);
  //xTaskCreatePinnedToCore(task2, "task2", 4096, NULL, 1, NULL, 1);
}

void loop() {
  M5.update();
  read_test();

}
