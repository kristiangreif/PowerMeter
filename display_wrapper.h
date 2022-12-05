#ifndef DISPLAY_WRAPPER_H
#define DISPLAY_WRAPPER_H

#include <Arduino.h>

void initDisplay();
void basicsScreen(char *voltage, char *current, char *power);
void capacityScreen(char *capacityAh, char *capacityWh);

#endif