#include "ui.h"
#include <M5Stack.h>
#include "sensor.h"

extern Plant plants[];
extern int selectedPlantIndex;
extern Sensory sensory;

Screen currentScreen = LIGHT;

void initializeUI() {
    M5.Lcd.setRotation(1);
    M5.Lcd.fillScreen(BLACK);
    drawNavigationBar();
    drawCurrentFrameContent();
}

void updateUI() {
    drawNavigationBar();
    drawCurrentFrameContent();
}

void drawNavigationBar() {
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.fillRect(0, 200, 320, 40, BLACK);

    M5.Lcd.setCursor(10, 210);
    M5.Lcd.print("A: Prev | C: Next | B: Select");
}

void drawCurrentFrameContent() {
    M5.Lcd.fillRect(0, 0, 320, 200, BLACK);
    M5.Lcd.setTextSize(2);

    switch (currentScreen) {
        case LIGHT:
            displayLightScreen();
            break;
        case PUMP:
            displayPumpScreen();
            break;
        case PLANT:
            displayPlantScreen();
            break;
        case VALUES:
            displayValuesScreen();
            break;
    }
}

void displayLightScreen() {
    SensorValues values = sensory.read();
    M5.Lcd.setCursor(10, 40);
    M5.Lcd.print("Light: ");
    M5.Lcd.println(values.currentLightCondition);

    M5.Lcd.setCursor(10, 70);
    M5.Lcd.print("Ideal Light: ");
    M5.Lcd.println(plants[selectedPlantIndex].idealLightCondition);
}

void displayPumpScreen() {
    M5.Lcd.setCursor(10, 40);
    M5.Lcd.print("Pump Status: ");
    M5.Lcd.println(sensory.isPumpRunning() ? "Running" : "Stopped");

    M5.Lcd.setCursor(10, 70);
    M5.Lcd.print("Press 'B' to ");
    M5.Lcd.println(sensory.isPumpRunning() ? "Stop Pump" : "Start Pump");
}

void displayPlantScreen() {
    M5.Lcd.setCursor(10, 40);
    M5.Lcd.print("Selected Plant: ");
    M5.Lcd.println(plants[selectedPlantIndex].name);

    M5.Lcd.setCursor(10, 70);
    M5.Lcd.print("Temp: ");
    M5.Lcd.print(plants[selectedPlantIndex].idealTemperature);
    M5.Lcd.println(" C");

    M5.Lcd.setCursor(10, 100);
    M5.Lcd.print("Humidity: ");
    M5.Lcd.print(plants[selectedPlantIndex].idealHumidity);
    M5.Lcd.println(" %");

    M5.Lcd.setCursor(10, 130);
    M5.Lcd.print("Light: ");
    M5.Lcd.print(plants[selectedPlantIndex].idealLightCondition);
    M5.Lcd.println(" lx");
}

void displayValuesScreen() {
    SensorValues values = sensory.read();
    M5.Lcd.setCursor(10, 40);
    M5.Lcd.print("Temp: ");
    M5.Lcd.print(values.currentTemprature);
    M5.Lcd.println(" C");

    M5.Lcd.setCursor(10, 70);
    M5.Lcd.print("Humidity: ");
    M5.Lcd.print(values.currentHumidity);
    M5.Lcd.println(" %");

    M5.Lcd.setCursor(10, 100);
    M5.Lcd.print("Light: ");
    M5.Lcd.print(values.currentLightCondition);
    M5.Lcd.println(" lx");
}
