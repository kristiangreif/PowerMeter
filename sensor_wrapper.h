#ifndef SENSOR_WRAPPER_H
#define SENSOR_WRAPPER_H

#include <Arduino.h>

#define BTN_PIN 23

typedef struct Readings{
    float voltage;
    float current;
    float power;
    float capacityAh;
    float capacityWh;
}READINGS;

bool setupINA();
float getVoltage();
float getCurrent();
void processReadings(READINGS *readings, unsigned long *lastTime);
void attachButtonCallbacks();

#endif