#include "ui.h"
#include <M5Stack.h>
#include "picture.h"
#include "plant.h"
#include <Adafruit_GFX.h>

#define DARK_GREEN  0x03E0
#define GRAY 0x7BEF 
#define GREEN 0x0ca6

extern Plant plants[];
extern Plant *selectedPlant; 

Screen frames[] = {SETTINGS,PUMP,PLANT,VALUES};
int currentFrame = 0; 

int selectedPlantIndex = 0;

unsigned long previousMillis = 0;
const unsigned long UPDATE_INTERVAL = 2000; 

String screenToString(Screen screen) {
  switch(screen) {
    case SETTINGS: return "Settings";
    case PUMP: return "Pumpe";
    case PLANT: return "Pflanze";
    case VALUES: return "Werte";
  }
}

void initializeUI(Sensory &sensor) {
    M5.Lcd.setRotation(1); 
    M5.Lcd.fillScreen(BLACK);
    drawNavigationBar();
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
        String currentScreenToString = screenToString(frames[i]);
        int textWidth = M5.Lcd.textWidth(currentScreenToString); 
        int textX = xStart + (320 / 4 - textWidth) / 2; 
        M5.Lcd.setCursor(textX, 10);
        M5.Lcd.print(currentScreenToString);
    }
    M5.Lcd.endWrite();
}


void drawCurrentFrameContent(Sensory &sensor,Network &network) {
    M5.Lcd.fillRect(1, 41, 318, 179, BLACK);

    switch(frames[currentFrame]) {
      case PLANT:drawPlantContent();break;
      case PUMP:drawPumpContent(sensor);break;
      case VALUES:drawValuesContent(sensor);break;
      case SETTINGS:drawSettingsContent(network);break;
    }
}

void drawSettingsContent(Network &network) {
  drawValueEntry(115,60,"-- Settings --","","");
  drawValueEntry(10,90,"Network state: ",network.status(),"");
  drawValueEntry(10,110,"Algorithmen state: ","","");
  drawValueEntry(10,140,"Waterlevel LED state:","","");

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
    drawValueEntry(10,150,"Fuellstand:",sensor.read().waterLevel ? "Voll" : "Leer","");
}


//If there is no type argument just pass empty ""
template <typename T>
void drawValueEntry(int x,int y,String desc,T value,String type) {
  M5.Lcd.setCursor(x, y);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.print(desc);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.print(value);
  M5.Lcd.print(type);
  }

//FRAME: VALUES
void drawValuesContent(Sensory &sensor) {
    M5.Lcd.fillRect(1, 30, 318, 179, BLACK);

    SensorValues values = sensor.read();
    String plantName = selectedPlant->getName();
    drawValueEntry(10,60,"Temperatur: ",values.currentTemprature," C");
    drawValueEntry(10,90, "Feuchtigkeit: ",values.currentHumidity," %");
    drawValueEntry(10,120,"Licht: ",values.currentLightCondition,"");

    //Ideal Values 
    //Temperatur
    drawValueEntry(150,60,plantName+"->",selectedPlant->idealTemperature," C");
    drawValueEntry(150,90,plantName+"->",selectedPlant->idealHumidity," %");
    drawValueEntry(150,120,plantName+"->",selectedPlant->idealLight,"");
    }
    //TODO: FRAME -> Licht / Statstik 



    //

    void updateUI(Sensory &sensor,Network &network) {

    //Navigate through the frames
    if (M5.BtnC.wasPressed()) {
        currentFrame = (currentFrame + 1) % 4;  
        drawNavigationBar();
        drawCurrentFrameContent(sensor,network);
    }

    if (M5.BtnA.wasPressed()) {
        currentFrame = (currentFrame - 1 + 4) % 4;  
        drawNavigationBar();
        drawCurrentFrameContent(sensor,network);
    }
    //

    switch(frames[currentFrame]) {
      case PLANT: {
         if (M5.BtnB.wasPressed()) {
            selectedPlantIndex = (selectedPlantIndex + 1) % 4;  
            drawCurrentFrameContent(sensor,network);
        }
      }
      break;
      case PUMP: {
        if (M5.BtnB.wasPressed()) {
          sensor.togglePump();  
          drawCurrentFrameContent(sensor,network);
        }
      }
      break;
      case VALUES: {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= UPDATE_INTERVAL) {
          previousMillis = currentMillis;
          sensor.update();  
          drawCurrentFrameContent(sensor,network);
        }
      }
      break;
      case SETTINGS: {
        break;
      }
    }
}

void selectPlant(Plant *plant) {
  plant = &plants[selectedPlantIndex];

}

int getSelectedPlantIndex() {
  return selectedPlantIndex;
}
