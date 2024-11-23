#include "input.h"
#include "ui.h"
#include <M5Stack.h>
#include "sensor.h"

extern Plant plants[];
extern int totalPlants;
extern int selectedPlantIndex;
extern Screen currentScreen;
extern Sensory sensory;

void processUserInput() {
    if (M5.BtnC.wasPressed()) {
        currentScreen = static_cast<Screen>((currentScreen + 1) % 4);
    }

    if (M5.BtnA.wasPressed()) {
        currentScreen = static_cast<Screen>((currentScreen - 1 + 4) % 4);
    }

    switch (currentScreen) {
        case PLANT:
            if (M5.BtnB.wasPressed()) {
                selectedPlantIndex = (selectedPlantIndex + 1) % totalPlants;
            }
            break;
        case PUMP:
            if (M5.BtnB.wasPressed()) {
                sensory.togglePump();
            }
            break;
        default:
            break;
    }
}
