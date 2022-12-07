#include "power_meter.h"
#include "sensor_wrapper.h"
#include "display_wrapper.h"
#include "server_wrapper.h"
#include "fonts.h"
#include <OneButton.h>

#define UPDATE_INTERVAL 1000

OneButton button(BTN_PIN, true, false);

bool measurementRunning = false;
byte screen = 0;

void toggle(){
    measurementRunning = !measurementRunning;
}

void changeScreen(){
    if(measurementRunning){
        screen += 1;
        if(screen > 1){
            screen = 0;
        }
    }
}

void setupMeter(){
    initDisplay();
    setupINA();

    welcomeScreen();

    initAP();
    initServer();

    button.attachLongPressStart(toggle);
    button.attachClick(changeScreen);
}

void measure(){
    if(measurementRunning){
        READINGS *readings = (READINGS*) malloc(sizeof(READINGS));
        char *json = (char*) malloc(JSON_SIZE);
        unsigned long lastTime = 0;
        unsigned long lastUpdate = 0;

        readings->capacityAh = 0.0;
        readings->capacityWh = 0.0;
        
        while (measurementRunning){
            processReadings(readings, &lastTime);

            displayScreen(screen, readings);

            if((millis() - lastUpdate) > UPDATE_INTERVAL){
                convertToJSON(readings, json);
                sendMessage(json);
                Serial.println(json);
                lastUpdate = millis();
            }
            
            handleConnections();
            button.tick();
        }
        free(json);
        free(readings);

        welcomeScreen();
    }
    handleConnections();
    button.tick();
}