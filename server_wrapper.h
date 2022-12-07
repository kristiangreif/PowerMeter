#ifndef SERVER_WRAPPER_H
#define SERVER_WRAPPER_H

#include <Arduino.h>
#include "sensor_wrapper.h"

void initAP();
void initServer();
void handleConnections();
void sendMessage(char *msg);

#endif