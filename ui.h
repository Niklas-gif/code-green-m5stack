#ifndef UI_H
#define UI_H

#include "sensor.h"
#include <M5Stack.h>

enum Screen { LIGHT, PUMP, PLANT, VALUES };

void initializeUI();

void updateUI();

void drawNavigationBar();

void drawCurrentFrameContent();

void displayLightScreen();

void displayPumpScreen();

void displayPlantScreen();

void displayValuesScreen();

#endif
