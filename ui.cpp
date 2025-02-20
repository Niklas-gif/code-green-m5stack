#include "ui.h"
#include <M5Stack.h>
#include "picture.h"
#include "plant.h"
#include "WiFiType.h"
#include <Adafruit_GFX.h>

#define DARK_GREEN  0x03E0
#define GRAY 0x7BEF 
#define GREEN 0x0ca6

extern Plant plants[];
extern Plant *selectedPlant;
extern bool algorithmIsRunning;

Screen frames[] = {SETTINGS,PUMP,PLANT,VALUES};
int currentFrame = 0; 

int selectedPlantIndex = 0;
int selectedSettingsOption = 0;

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

String wifiStatus(Network &network) {
  switch(network.status()) {
    case wl_status_t::WL_NO_SHIELD: return "MISSING SHIELD";
    case wl_status_t::WL_IDLE_STATUS: return "IDLE";
    case wl_status_t::WL_NO_SSID_AVAIL: return "SSID AVAIL";
    case wl_status_t::WL_SCAN_COMPLETED: return "SCAN COMPLETED";
    case wl_status_t::WL_CONNECTED: return "CONNECTED";
    case wl_status_t::WL_CONNECT_FAILED: return "CONNECTION FAILED";
    case wl_status_t::WL_CONNECTION_LOST: return "CONNECTION LOST";
    case wl_status_t::WL_DISCONNECTED: return "DISCONNECTED";
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
      case SETTINGS:drawSettingsContent(network,sensor);break;
    }
}

void drawSettingsContent(Network &network,Sensory &sensor) {
  SettingsOption so = (SettingsOption) selectedSettingsOption;
  drawValueEntry(115,60,"-- Settings --", "", "", false);
  drawValueEntry(10,90,"Network state: ", wifiStatus(network), "", so == NETWORK ? true : false);
  drawValueEntry(10,120,"Auto plant watering: ", algorithmIsRunning ? " ON" : " OFF", "", so == AUTO ? true : false);
  drawValueEntry(10,150,"Waterlevel LED:", sensor.waterLevelLEDState() ? " ON" : " OFF", "", so == WATERLEVEL_LED ? true : false);
  M5.Lcd.setTextColor(GRAY);
  M5.Lcd.setCursor(185, 90);
  M5.Lcd.print("To change settings");
  M5.Lcd.setCursor(185, 105);
  M5.Lcd.print("hold the select button");
  M5.Lcd.setCursor(185, 120);
  M5.Lcd.print("for 1 second.");
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
    drawValueEntry(10,150,"Fuellstand:",sensor.read().waterLevel ? "Voll" : "Leer","",false);
}


//If there is no type argument just pass empty ""
template <typename T>
void drawValueEntry(int x,int y,String desc,T value,String type,bool isSelected) {
  M5.Lcd.setCursor(x, y);
  M5.Lcd.setTextColor(isSelected ? ORANGE : WHITE);
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
    drawValueEntry(10,60,"Temperatur: ",values.currentTemprature," C",false);
    drawValueEntry(10,90, "Feuchtigkeit: ",values.currentHumidity," %",false);
    drawValueEntry(10,120,"Licht: ",values.currentLightCondition,"",false);
    drawValueEntry(10,150,"Bodenfeuchtigkeit: ",values.rawADC,"",false);

    //Ideal Values 
    //Temperatur
    drawValueEntry(150,60,plantName+"->",selectedPlant->idealTemperature," C",false);
    drawValueEntry(150,90,plantName+"->",selectedPlant->idealHumidity," %",false);
    drawValueEntry(150,120,plantName+"->",selectedPlant->idealLight,"",false);
    }

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
        unsigned long currentMillis = millis();
        static bool actionTriggered = false;

    if (M5.BtnB.pressedFor(1000)) {
        if (!actionTriggered) {
            actionTriggered = true;
            switch ((SettingsOption)selectedSettingsOption) {
                case NETWORK: {network.send(sensor, 0); break; }
                case AUTO: { algorithmIsRunning = !algorithmIsRunning; break; }
                case WATERLEVEL_LED: { sensor.toggleWaterLevelLED(); break; }
            }
        }
    } else if (M5.BtnB.wasReleased()) {
        actionTriggered = false;
        selectedSettingsOption = (selectedSettingsOption + 1) % 3;
    }
        if (currentMillis - previousMillis >= 500) {
          previousMillis = currentMillis;
          drawCurrentFrameContent(sensor,network);
        }
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
