#include "display_wrapper.h"
#include "sensor_wrapper.h"
#include "server_wrapper.h"
#include "fonts.h"
#include <OneButton.h>

#define UPDATE_INTERVAL 1000

OneButton button(BTN_PIN, true, false);

bool measurementRunning = false;
byte screen = 0;

void setup(){
    Serial.begin(115200);
    initDisplay();
    if(!setupINA()){
        Serial.println("Could not init INA226");
    }

    initAP();
    initServer();

    button.attachLongPressStart(toggle);
    button.attachClick(changeScreen);
}

void loop(){
    if(measurementRunning){
        READINGS *readings = (READINGS*) malloc(sizeof(READINGS));
        char *json = (char*) malloc(JSON_SIZE);
        unsigned long lastTime = 0;
        unsigned long lastUpdate = 0;

        readings->capacityAh = 0.0;
        readings->capacityWh = 0.0;
        

        while (measurementRunning){
            processReadings(readings, &lastTime);
            convertToString(readings);

            if((millis() - lastUpdate) > UPDATE_INTERVAL){
                convertToJSON(readings, json);
                sendMessage(json);
                Serial.println(json);
                lastUpdate = millis();
            }
            switch (screen){
                case 0:
                    basicsScreen(readings->strVoltage, readings->strCurrent, readings->strPower);
                    break;
                
                case 1:
                    capacityScreen(readings->strCapacityAh, readings->strCapacityWh);
                    break;
            }
            handleConnections();
            button.tick();
        }
        free(json);
        free(readings);
    }
    handleConnections();
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