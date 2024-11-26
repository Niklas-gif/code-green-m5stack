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

    // Rahmen um das gesamte Display
    M5.Lcd.drawRect(0, 0, 320, 240, GREEN);

    // Navigation Bar unten
    M5.Lcd.fillRect(0, 220, 320, 20, GREEN);
    M5.Lcd.setTextColor(BLACK);
    
    M5.Lcd.setCursor(10, 225);  
    M5.Lcd.print("Previous");
    
    M5.Lcd.setCursor(150, 225);  
    M5.Lcd.print("Select");

    M5.Lcd.setCursor(300, 225);  
    M5.Lcd.print("Next"); 

    // Navigation Bar oben
    for (int i = 0; i < 4; i++) {  
        int xStart = i * (320 / 4);  
        if (i == currentFrame) {
            M5.Lcd.fillRect(xStart, 0, 320 / 4, 30, GREEN); 
            M5.Lcd.setTextColor(WHITE);  
        } else {
            M5.Lcd.fillRect(xStart, 0, 320 / 4, 30, BLACK); 
            M5.Lcd.setTextColor(GRAY);   
        }
        
        // Rahmen um jeden Abschnitt
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

void drawPlantContent() {

    int blockWidth = 160;
    int blockHeight = 95;

    for (int i = 0; i < 2; i++) {  // Zeilen
        for (int j = 0; j < 2; j++) {  // Spalten
            int xStart = j * blockWidth;
            int yStart = 30 + i * blockHeight; // 30 für direkte Verbindung mit der Navigationsleiste

            // Block zeichnen
            M5.Lcd.drawRect(xStart, yStart, blockWidth, blockHeight, GREEN);

            // Pflanze in den Block zeichnen
            int plantIndex = i * 2 + j;
            if (plantIndex < 4) {  // Sicherstellen, dass es nur 4 Pflanzen gibt
                String plantName = plants[plantIndex].getName();
                
                // Textfarbe abhängig davon, ob die Pflanze ausgewählt ist
                if (selectedPlantIndex == plantIndex) {
                    M5.Lcd.setTextColor(0xFFA500);  // Orange für die ausgewählte Pflanze
                } else {
                    M5.Lcd.setTextColor(WHITE);  // Standardfarbe für andere Pflanzen
                }
                
                
                M5.Lcd.setFont(&FreeMono9pt7b); 

                // Vertikale Textdarstellung
                int textX = xStart + 10;  // X-Position
                int textY = yStart + 20;  // Y-Startposition

                for (int k = 0; k < plantName.length(); k++) {
                    M5.Lcd.setCursor(textX, textY + k * 12);  // Verschiebung für vertikalen Text
                    M5.Lcd.print(plantName.charAt(k));  // Nur das aktuelle Zeichen drucken
                }

                M5.Lcd.setFont();

                // Bild zentriert im Block
                if (selectedPlantIndex == plantIndex) {
                    // Farbiges Bild, wenn ausgewählt
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
                    // Graues Bild, wenn nicht ausgewählt
                    if (plantName == "Kaktus") {
                        M5.Lcd.drawBitmap(xStart + 50, yStart + 10, 82, 80, grey_kaktus); // Graues Bild
                    } else if (plantName == "Bonsai") {
                        M5.Lcd.drawBitmap(xStart + 50, yStart + 15, 74, 70, grey_bonsai); // Graues Bild
                    } else if (plantName == "Orchid") {
                        M5.Lcd.drawBitmap(xStart + 50, yStart + 15, 74, 70, grey_orchid); // Graues Bild
                    } else if (plantName == "Agave") {
                        M5.Lcd.drawBitmap(xStart + 50, yStart + 15, 74, 70, grey_agave); // Graues Bild
                    }
                }
            }
        }
    }
}


void drawPumpContent(Sensory &sensor) {
    M5.Lcd.setCursor(10, 60);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.print("Pumpensteuerung:");
    M5.Lcd.setCursor(10, 90);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.printf("Pumpe: %s", sensor.isPumpRunning() ? "ON" : "OFF");
}

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
    M5.Lcd.print(values.cu