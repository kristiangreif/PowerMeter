#include "power_meter.h"

void setup(){
    Serial.begin(115200);
    setupMeter();
}

void loop(){
    measure();
}