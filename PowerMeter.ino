#include "display_wrapper.h"
#include "sensor_wrapper.h"
#include "fonts.h"
#include <OneButton.h>

OneButton button(BTN_PIN, true, false);

bool measurementRunning = false;
byte screen = 0;

void setup(){
    Serial.begin(115200);
    initDisplay();
    if(!setupINA()){
        Serial.println("Could not init INA226");
    }
    button.attachLongPressStart(toggle);
    button.attachClick(changeScreen);
}

void loop(){
    if(measurementRunning){
        READINGS *readings = (READINGS*) malloc(sizeof(READINGS));
        unsigned long lastTime = 0;

        readings->capacityAh = 0.0;
        readings->capacityWh = 0.0;
        while (measurementRunning){
            processReadings(readings, &lastTime);
            switch (screen){
                case 0:
                    basicsScreen(readings->voltage, readings->current, readings->power);
                    break;
                
                case 1:
                    capacityScreen(readings->capacityAh, readings->capacityWh);
                    break;
            }
            button.tick();
        }
        free(readings);
    }
    button.tick();
}

void toggle(){
    measurementRunning = !measurementRunning;
}

void changeScreen(){
    screen += 1;
    if(screen > 1){
        screen = 0;
    }
}