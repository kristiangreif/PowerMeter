#ifndef DISPLAY_WRAPPER_H
#define DISPLAY_WRAPPER_H

#include <Arduino.h>
#include "sensor_wrapper.h"

void initDisplay();
void welcomeScreen();
void basicsScreen(char *voltage, char *current, char *power);
void capacityScreen(char *capacityAh, char *capacityWh);
void displayScreen(byte n, READINGS *readings);

#endif