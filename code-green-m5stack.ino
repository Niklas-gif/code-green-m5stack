#include <M5Stack.h>
#include "FakeSensor.h"
//#include <M5UnitENV.h>

//SCREEN RES H = 240 W = 320

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
  //M5.Lcd.clear();
  //M5.Lcd.setCursor(32,32);
  //M5.Lcd.print(temp_value + fakeSensor.read() + "C");
    M5.Lcd.fillRect(0, 32, 320 , 22, BLACK);
    M5.Lcd.drawString(temp_value + fakeSensor.read() + "C",32,32);
  //delay(1000);
}

// #######################
// # TEST AND FAKE STUFF #
// #######################


void task1(void* pvParameters) { 
    Serial.println("Task 1 started");
    for (;;) {
      if (xSemaphoreTake(counterMutex, portMAX_DELAY)) {
          if(M5.BtnA.isPressed()) {
            counter = 0;
          }
          counter++;
        xSemaphoreGive(counterMutex);
      }
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void task2(void* pvParameters) { 
    Serial.println("Task 2 started");
    for (;;) {  
      M5.update();
      read_test();
      if (xSemaphoreTake(counterMutex, portMAX_DELAY)) {
        M5.Lcd.fillRect(0, 64, 320, 22, BLACK);
        M5.Lcd.drawString("Counter:" + String(counter),32,64);
        xSemaphoreGive(counterMutex);
      }
      //delay(1000); 
      vTaskDelay(300 / portTICK_PERIOD_MS);
      //M5.Lcd.fillScreen(BLACK);
    }
}

void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Power.begin();
  fake_init();

  counterMutex = xSemaphoreCreateMutex();
  xTaskCreatePinnedToCore(task1, "task1", 8192, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(task2, "task2", 8192, NULL, 1, NULL, 1);
}

void loop() {
  //M5.update();
  //read_test();

}
