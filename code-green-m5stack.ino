#include <M5Stack.h>
#include <Wire.h>   
#include <SHT4X.h>  // Heat Sensor
#include <Digital_Light_TSL2561.h> 
#include "picture.cpp"


#define DARK_GREEN 0x03E0
#define ORANGE 0xff6e00


//Orange knallig 0xF860

//Limette 0xff6e00

String frames[] = {"LIGHT", "PUMP", "Pflanze", "Werte"};
int currentFrame = 0; 

String plants[] = {"Kaktus", "Bonsai", "Orchidee", "Agave"};
int selectedPlantIndex = 0; 

#define GRAY 0x7BEF // Grau

// Pumpe
#define PUMP_PIN  26
bool pumpState = false;

// Temperatur und Feuchtigkeit
SHT4X sht4;

// Sensor für Temperatur und Feuchtigkeit
float temperature = 0.0;
float humidity = 0.0;

// Preset-Werte
float idealTemperature[] = {30.0, 22.0, 25.0, 30.0};  
float idealHumidity[] = {10.0, 50.0, 60.0, 30.0};     

unsigned long previousMillis = 0; // Timer (s.u)
const long interval = 10000; // Aktualisierung der Sensorwerte (10 Sekunden)

void setup() {
    M5.begin();

    // Bildschirm
    M5.Lcd.setRotation(1); // Nicht entfernen, ansonsten steht Arduino "kopf"
    M5.Lcd.fillScreen(BLACK);
    drawNavigationBar(); 
    drawCurrentFrameContent();

    // Pumpe
    pinMode(PUMP_PIN, OUTPUT);
    digitalWrite(PUMP_PIN, LOW); // Pumpe startet im "Aus"-Zustand

    // Heat Sensor
    if (!sht4.begin()) {
        Serial.println("SHT4X Sensor nicht gefunden");
        while (1) delay(1);
    }
}

void drawNavigationBar() {
    M5.Lcd.fillRect(0, 0, 320, 40, BLACK); 

    //Leiste unten
    M5.Lcd.fillRect(0, 220, 320, 20, ORANGE);  // Die untere Leiste (dünn, 20px hoch)

    // Text für A-Button (links) und C-Button (rechts)
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setCursor(10, 225);  // Position für den A-Button Text
    M5.Lcd.print("A");

    M5.Lcd.setCursor(300, 225);  // Position für den C-Button Text (rechts)
    M5.Lcd.print("C");

    // Leiste oben
    for (int i = 0; i < 4; i++) {  
        int xStart = i * (320 / 4);  

        // Aktiver Frame
        if (i == currentFrame) {
            M5.Lcd.fillRect(xStart, 0, 320 / 4, 30, DARK_GREEN); 
            M5.Lcd.setTextColor(WHITE);  
        } 
        // Inaktiver Frame
        else {
            M5.Lcd.fillRect(xStart, 0, 320 / 4, 30, BLACK); 
            M5.Lcd.setTextColor(GRAY);   
        }
        
        // Rahmen um jedes Frame
        M5.Lcd.drawRect(xStart, 0, 320 / 4, 30, ORANGE);

        // Text des Frames zentriert anzeigen
        int textWidth = frames[i].length() * 6; 
        int textX = xStart + (320 / 4 - textWidth) / 2; 
        M5.Lcd.setCursor(textX, 10);
        M5.Lcd.print(frames[i]);
    }

}

void drawCurrentFrameContent() {
    M5.Lcd.fillRect(0, 40, 320, 180, BLACK);

    if (frames[currentFrame] == "Pflanze") {
        M5.Lcd.setCursor(10, 60);
        M5.Lcd.setTextColor(WHITE);
        
        M5.Lcd.setCursor(10, 90);
        M5.Lcd.setTextColor(DARK_GREEN);
        M5.Lcd.print(plants[selectedPlantIndex]); 
        
        // Kaktus-Bitmap anzeigen
        if (plants[selectedPlantIndex] == "Kaktus") {
            M5.Lcd.drawBitmap(105, 55, 130, 158, kaktus);
        
        } else if (plants[selectedPlantIndex] == "Bonsai") {
          M5.Lcd.drawBitmap(77, 60, 179, 152, bonsai);
        
        } else if (plants[selectedPlantIndex] == "Orchidee") {
          M5.Lcd.drawBitmap(97, 60, 130, 160, orchid);

        } else if (plants[selectedPlantIndex] == "Agave") {
          M5.Lcd.drawBitmap(97, 55, 156, 160, agave);
        }

        M5.Lcd.setCursor(145, 222); //(zentriert über Button B)
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.print("next");

    } else if (frames[currentFrame] == "PUMP") {
        M5.Lcd.setCursor(10, 60);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.print("Pumpensteuerung:");
        
        M5.Lcd.setCursor(10, 90);
        M5.Lcd.setTextColor(DARK_GREEN);
        M5.Lcd.printf("Pumpe: %s", pumpState ? "ON" : "OFF");

        
    } else if (frames[currentFrame] == "Werte") {
        M5.Lcd.setCursor(10, 60);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.print("Temperatur: ");
        M5.Lcd.setCursor(10, 90);
        M5.Lcd.setTextColor(DARK_GREEN);
        M5.Lcd.print(temperature);
        M5.Lcd.print(" C");
        
        M5.Lcd.setCursor(10, 120);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.print("Feuchtigkeit: ");
        M5.Lcd.setCursor(10, 150);
        M5.Lcd.setTextColor(DARK_GREEN);
        M5.Lcd.print(humidity);
        M5.Lcd.print(" %");

        M5.Lcd.setCursor(200, 60);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.print("Ideal Temp: ");
        M5.Lcd.setCursor(200, 90);
        M5.Lcd.setTextColor(DARK_GREEN);
        M5.Lcd.print(idealTemperature[selectedPlantIndex]);
        M5.Lcd.print(" C");

        M5.Lcd.setCursor(200, 120);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.print("Ideal Feuch: ");
        M5.Lcd.setCursor(200, 150);
        M5.Lcd.setTextColor(DARK_GREEN);
        M5.Lcd.print(idealHumidity[selectedPlantIndex]);
        M5.Lcd.print(" %");
    } 
}

void loop() {
    M5.update();

    // Framewechsel 
    if (M5.BtnC.wasPressed()) {
        currentFrame = (currentFrame + 1) % 4; 
        drawNavigationBar(); 
        drawCurrentFrameContent(); 
    }

    if (frames[currentFrame] == "Pflanze") {
        if (M5.BtnA.wasPressed()) {
            selectedPlantIndex = (selectedPlantIndex - 1 + 4) % 4; 
            drawCurrentFrameContent();
        }

        if (M5.BtnB.wasPressed()) {
            selectedPlantIndex = (selectedPlantIndex + 1) % 4; 
            drawCurrentFrameContent();
        }
    }

    if (frames[currentFrame] == "PUMP") {
        if (M5.BtnB.wasPressed()) {
            pumpState = !pumpState; 
            digitalWrite(PUMP_PIN, pumpState ? HIGH : LOW); 
            drawCurrentFrameContent(); 
        }
    }

    if (frames[currentFrame] == "Werte") {
        unsigned long currentMillis = millis(); 
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis; 

            if (sht4.update()) {
                temperature = sht4.cTemp; 
                humidity = sht4.humidity; 
            }
            drawCurrentFrameContent();
        }
    }

    delay(100); 
}