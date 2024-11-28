#ifndef UI_H
#define UI_H

#include "sensor.h"
#include "plant.h"
#include <M5Stack.h>

typedef enum Screen { LIGHT, PUMP, PLANT, VALUES } Screen;

void initializeUI(Sensory &sensor);
void selectPlant(Plant *plant);
int getSelectedPlantIndex();
void updateUI(Sensory &sensor);


//This function are private !!!
template <typename T>
void drawValueEntry(int x,int y,String desc,T value,String type);
String screenToString(Screen screen);
void drawNavigationBar();
void drawCurrentFrameContent(Sensory &sensor);
void drawPlantContent();
void drawPumpContent(Sensory &sensor);
void drawValuesContent(Sensory &sensor);

#endif
