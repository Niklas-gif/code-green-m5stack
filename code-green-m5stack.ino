#include <M5Stack.h>
 
void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(4);
  M5.Lcd.setTextColor(GREEN); 
  M5.Lcd.print("CODE GREEN");
  
}

void loop() {
  M5.update();

}
