#include "ui.h"
#include <M5Stack.h>
#include "sensor.h"
#include "picture.h"
#include "plant.h"
#include <Adafruit_GFX.h>

#define DARK_GREEN  0x03E0
#define GRAY 0x7BEF 
#define GREEN 0x0ca6

extern Plant plants[];  

Sensory sensor;

String frames[] = {"Licht", "Pumpe", "Pflanze", "Werte"};
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

    M5.Lcd.drawRect(0, 0, 320, 240, GREEN);

    M5.Lcd.fillRect(0, 220, 320, 20, GREEN);
    M5.Lcd.setTextColor(BLACK);

    //TODO: Change font 
    
    M5.Lcd.setCursor(50, 225);  
    M5.Lcd.print("Previous");
    
    M5.Lcd.setCursor(115, 225);  
    M5.Lcd.print("|    Select    |");

    M5.Lcd.setCursor(235, 225);  
    M5.Lcd.print("Next"); 

    for (int i = 0; i < 4; i++) {  
        int xStart = i * (320 / 4);  
        if (i == currentFrame) {
            M5.Lcd.fillRect(xStart, 0, 320 / 4, 30, GREEN); 
            M5.Lcd.setTextColor(WHITE);  
        } else {
            M5.Lcd.fillRect(xStart, 0, 320 / 4, 30, BLACK); 
            M5.Lcd.setTextColor(GRAY);   
        }
        
        M5.Lcd.drawRect(xStart, 0, 320 / 4, 30, GREEN);

        int textWidth = M5.Lcd.textWidth(frames[i]); 
        int textX = xStart + (320 / 4 - textWidth) / 2; 
        M5.Lcd.setCursor(textX, 10);
        M5.Lcd.print(frames[i]);
    }
    M5.Lcd.endWrite();
}


void drawCurrentFrameContent(Sensory &sensor) {
    M5.Lcd.fillRect(1, 41, 318, 179, BLACK);

    if (frames[currentFrame] == "Pflanze") {
        drawPlantContent();
    } 
    else if (frames[currentFrame] == "Pumpe") {
        drawPumpContent(sensor);
    } 
    else if (frames[currentFrame] == "Werte") {
        drawValuesContent(sensor);
    }
}

//FRAME: PFLANZEN

void drawPlantContent() {

    int blockWidth = 160;
    int blockHeight = 95;

    for (int i = 0; i < 2; i++) { 
        for (int j = 0; j < 2; j++) {  
            int xStart = j * blockWidth;
            int yStart = 30 + i * blockHeight; 

            M5.Lcd.drawRect(xStart, yStart, blockWidth, blockHeight, GREEN);

            int plantIndex = i * 2 + j;
            if (plantIndex < 4) {  
                String plantName = plants[plantIndex].getName();
                
                if (selectedPlantIndex == plantIndex) {
                    M5.Lcd.setTextColor(0xFFA500);  
                } else {
                    M5.Lcd.setTextColor(WHITE);  
                }
                
                
                M5.Lcd.setFont(&FreeMono9pt7b); 

                int textX = xStart + 10;  
                int textY = yStart + 20;  

                for (int k = 0; k < plantName.length(); k++) {
                    M5.Lcd.setCursor(textX, textY + k * 12);  
                    M5.Lcd.print(plantName.charAt(k)); 
                }

                M5.Lcd.setFont();

                if (selectedPlantIndex == plantIndex) {
                    if (plantName == "Kaktus") {
                        M5.Lcd.drawBitmap(xStart + 50, yStart + 10, 82, 80, kaktus);
                    } else if (plantName == "Bonsai") {
                        M5.Lcd.drawBitmap(xStart + 50, yStart + 15, 74, 70, bonsai);
                    } else if (plantName == "Orchid") {
                        M5.Lcd.drawBitmap(xStart + 50, yStart + 15, 74, 70, orchid);
                    } else if (plantName == "Agave") {
                        M5.Lcd.drawBitmap(xStart + 50, yStart + 15, 74, 70, agave);
                    }
                } else {
                    if (plantName == "Kaktus") {
                        M5.Lcd.drawBitmap(xStart + 50, yStart + 10, 82, 80, grey_kaktus); 
                    } else if (plantName == "Bonsai") {
                        M5.Lcd.drawBitmap(xStart + 50, yStart + 15, 74, 70, grey_bonsai); 
                    } else if (plantName == "Orchid") {
                        M5.Lcd.drawBitmap(xStart + 50, yStart + 15, 74, 70, grey_orchid); 
                    } else if (plantName == "Agave") {
                        M5.Lcd.drawBitmap(xStart + 50, yStart + 15, 74, 70, grey_agave); 
                    }
                }
            }
        }
    }
}


//FRAME: PUMPE


void drawPumpContent(Sensory &sensor) {
    M5.Lcd.setCursor(10, 60);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.print("Pumpensteuerung:");
    M5.Lcd.setCursor(10, 90);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.printf("Pumpe: %s", sensor.isPumpRunning() ? "ON" : "OFF");
}

//FRAME: VALUES
//TODO: Values vervollständigen + idealVales einsetzen 

void drawValuesContent(Sensory &sensor) {
    M5.Lcd.fillRect(1, 30, 318, 179, BLACK);

    SensorValues values = sensor.read();
    
    M5.Lcd.setCursor(10, 60);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.print("Temperatur: ");
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.print(values.currentTemprature);
    M5.Lcd.print(" C");
    
    M5.Lcd.setCursor(10, 90);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.print("Feuchtigkeit: ");
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.print(values.currentHumidity);
    M5.Lcd.print(" %");

    M5.Lcd.setCursor(10, 120);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.print("Licht: ");
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.print(values.currentLightCondition); 
    
    }


    //TODO: FRAME -> Licht 



    //

    void updateUI(Sensory &sensor) {
    if (M5.BtnC.wasPressed()) {
        currentFrame = (currentFrame + 1) % 4;  
        drawNavigationBar();
        drawCurrentFrameContent(sensor);
    }

    if (M5.BtnA.wasPressed()) {
        currentFrame = (currentFrame - 1 + 4) % 4;  
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
    else if (frames[currentFrame] == "Pumpe" && M5.BtnB.wasPressed()) {
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