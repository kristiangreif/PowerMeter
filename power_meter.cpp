#include "power_meter.h"
#include "sensor_wrapper.h"
#include "display_wrapper.h"
#include "server_wrapper.h"
#include "database_wrapper.h"
#include "fonts.h"
#include <OneButton.h>

#define UPDATE_INTERVAL 1000
#define PROTECTION_DELAY 2000

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
    pinMode(RELAY_PIN, OUTPUT);

    wifiConnectScreen();
    initAP();

    dbConnectScreen();
    initDB();

    welcomeScreen();

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
        unsigned long protectionTriggerTime = 0;
        bool protectionTimerActivated = false;

        readings->capacityAh = 0.0;
        readings->capacityWh = 0.0;
        
        while(measurementRunning){
            processReadings(readings, &lastTime);

            if(protectionTriggered(readings)){
                if(!protectionTimerActivated){
                    protectionTriggerTime = millis();
                    protectionTimerActivated = true;
                } else{
                    if((millis() - protectionTriggerTime) >= PROTECTION_DELAY){
                        digitalWrite(RELAY_PIN, HIGH);
                    }
                }
            } else{
                digitalWrite(RELAY_PIN, LOW);
                protectionTimerActivated = false;
            }

            displayScreen(screen, readings);

            if((millis() - lastUpdate) > UPDATE_INTERVAL){
                serializeReadings(readings, json);
                sendMessage(json);
                Serial.println(json);

                int dbWriteStatus = writeReadings(readings);

                lastUpdate = millis();
            }
            
            handleConnections();
            button.tick();
        }
        free(json);
        free(readings);

        resetLimits();

        welcomeScreen();
    }
    handleConnections();
    button.tick();
}