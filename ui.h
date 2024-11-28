#ifndef UI_H
#define UI_H

#include "sensor.h"
#include "plant.h"
#include <M5Stack.h>

enum Screen { LIGHT, PUMP, PLANT, VALUES };
void initializeUI(Sensory &sensor);
void drawNavigationBar();
void drawCurrentFrameContent(Sensory &sensor);
void updateUI(Sensory &sensor);

void drawPlantContent();
void drawPumpContent(Sensory &sensor);
void drawValuesContent(Sensory &sensor);

void selectPlant(Plant *plant);
int getSelectedPlantIndex();


//This function are private !!!
template <typename T>
void drawValueEntry(int x,int y,String desc,T value,String type); 

#endif
