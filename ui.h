#ifndef UI_H
#define UI_H

#include "sensor.h"
#include "plant.h"
#include "network.h"
#include <M5Stack.h>

typedef enum Screen { SETTINGS, PUMP, PLANT, VALUES } Screen;
typedef enum SettingsOption { NETWORK, AUTO, WATERLEVEL_LED} SettingsOption;

void initializeUI(Sensory &sensor);
void selectPlant(Plant *plant);
int getSelectedPlantIndex();
void updateUI(Sensory &sensor,Network &network);

template <typename T>
void drawValueEntry(int x,int y,String desc,T value,String type,bool isSelected);
String screenToString(Screen screen);
String wifiStatus(Network &netwok);
void drawNavigationBar();
void drawCurrentFrameContent(Sensory &sensor,Network &network);
void drawPlantContent();
void drawPumpContent(Sensory &sensor);
void drawValuesContent(Sensory &sensor);
void drawSettingsContent(Network &network,Sensory &sensor);

#endif
