#include "ui.h"
#include <M5Stack.h>
#include "sensor.h"
#include "picture.h"
#include "plant.h"

// Farbcodes definieren
#define DARK_GREEN  0x03E0
#define GRAY 0x7BEF 
#define ORANGE 0xFF6E

extern Plant plants[];  

Sensory sensor;

String frames[] = {"LIGHT", "PUMP", "Pflanze", "Werte"};
int currentFrame = 0; 

int selectedPlantIndex = 0;

unsigned long previousMillis = 0;
const unsigned long interval = 2000; 

void initializeUI() {
    M5.Lcd.setRotation(1); 
    M5.Lcd.fillScreen(BLACK);
    drawNavigationBar();
    drawCurrentFrameContent(sensor); 
}


void drawNavigationBar() {
    M5.Lcd.startWrite();
    //M5.Lcd.fillRect(0, 0, 320, 40, BLACK); 

    M5.Lcd.fillRect(0, 220, 320, 20, ORANGE);

    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setCursor(10, 225);  
    M5.Lcd.print("A"); +
    M5.Lcd.setCursor(300, 225);  
    M5.Lcd.print("C"); 

    for (int i = 0; i < 4; i++) {  
        int xStart = i * (320 / 4);  

        if (i == currentFrame) {
            M5.Lcd.fillRect(xStart, 0, 320 / 4, 30, DARK_GREEN); 
            M5.Lcd.setTextColor(WHITE);  
        } else {
            M5.Lcd.fillRect(xStart, 0, 320 / 4, 30, BLACK); 
            M5.Lcd.setTextColor(GRAY);   
        }
        
        M5.Lcd.drawRect(xStart, 0, 320 / 4, 30, ORANGE);
        int textWidth = frames[i].length() * 6; 
        int textX = xStart + (320 / 4 - textWidth) / 2; 
        M5.Lcd.setCursor(textX, 10);
        M5.Lcd.print(frames[i]);
    }
    M5.Lcd.endWrite();
}


void drawCurrentFrameContent(Sensory &sensor) {
    M5.Lcd.fillRect(0, 40, 320, 180, BLACK);

    if (frames[currentFrame] == "Pflanze") {
        M5.Lcd.setCursor(10, 60);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.print(plants[selectedPlantIndex].getName()); 
        
        if (plants[selectedPlantIndex].getName() == "Kaktus") {
            M5.Lcd.drawBitmap(105, 55, 130, 158, kaktus);
        } else if (plants[selectedPlantIndex].getName() == "Bonsai") {
            M5.Lcd.drawBitmap(77, 60, 179, 152, bonsai);
        } else if (plants[selectedPlantIndex].getName() == "Orchidee") {
            M5.Lcd.drawBitmap(97, 60, 130, 160, orchid);
        } else if (plants[selectedPlantIndex].getName() == "Agave") {
            M5.Lcd.drawBitmap(97, 55, 156, 160, agave);
        }
    } 
    
    else if (frames[currentFrame] == "PUMP") {
        M5.Lcd.setCursor(10, 60);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.print("Pumpensteuerung:");
        M5.Lcd.setCursor(10, 90);
        M5.Lcd.setTextColor(DARK_GREEN);
        M5.Lcd.printf("Pumpe: %s", sensor.isPumpRunning() ? "ON" : "OFF");
    } 
    
    else if (frames[currentFrame] == "Werte") {
        SensorValues values = sensor.read();
        M5.Lcd.setCursor(10, 60);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.print("Temperatur: ");
        M5.Lcd.setTextColor(DARK_GREEN);
        M5.Lcd.print(values.currentTemprature);
        M5.Lcd.print(" C");
        M5.Lcd.setCursor(10, 120);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.print("Feuchtigkeit: ");
        M5.Lcd.setTextColor(DARK_GREEN);
        M5.Lcd.print(values.currentHumidity);
        M5.Lcd.print(" %");
    }
}

void changeFrame(Sensory &sensor) {
    if (M5.BtnC.wasPressed()) {
        currentFrame = (currentFrame + 1) % 4;
        drawNavigationBar();
        drawCurrentFrameContent(sensor);
    }

    if (frames[currentFrame] == "Pflanze") {
        if (M5.BtnA.wasPressed()) {
            selectedPlantIndex = (selectedPlantIndex - 1 + 4) % 4;
            drawCurrentFrameContent(sensor);
        }
        if (M5.BtnB.wasPressed()) {
            selectedPlantIndex = (selectedPlantIndex + 1) % 4;
            drawCurrentFrameContent(sensor);
        }
    } 
    
    else if (frames[currentFrame] == "PUMP" && M5.BtnB.wasPressed()) {
        sensor.togglePump();
        drawCurrentFrameContent(sensor);
    } 
    
    else if (frames[currentFrame] == "Werte") {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            sensor.update();
            drawCurrentFrameContent(sensor);
        }
    }
    
}





