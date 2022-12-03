#ifndef DISPLAY_WRAPPER_H
#define DISPLAY_WRAPPER_H

#include <Arduino.h>

void initDisplay();
void basicsScreen(float voltage, float current, float power);
void capacityScreen(float capacityAh, float capacityWh);

#endif