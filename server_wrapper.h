#ifndef SERVER_WRAPPER_H
#define SERVER_WRAPPER_H

#include <Arduino.h>

void initAP();
void initServer();
void processDNSRequests();
void sendMessage();

#endif