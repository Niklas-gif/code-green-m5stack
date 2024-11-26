#ifndef UI_H
#define UI_H

#include "sensor.h"
#include <M5Stack.h>

enum Screen { LIGHT, PUMP, PLANT, VALUES };

void initializeUI();
void updateUI();
void drawNavigationBar();
void drawCurrentFrameContent(Sensory &sensor);
void changeFrame(Sensory &sensor);

void drawPlantContent();
void drawPumpContent(Sensory &sensor);
void drawValuesContent(Sensory &sensor);

#endif
