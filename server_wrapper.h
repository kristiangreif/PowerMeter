#ifndef SERVER_WRAPPER_H
#define SERVER_WRAPPER_H

#include <Arduino.h>
#include "sensor_wrapper.h"

extern bool fetchDbReadings;
extern char queryTimeFrom[21];
extern char queryTimeTo[21];

void initAP();
void initServer();
void handleConnections();
void sendMessage(const char *msg);

#endif