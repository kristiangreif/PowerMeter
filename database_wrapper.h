#ifndef DATABASE_WRAPPER_H
#define DATABASE_WRAPPER_H

#include <Arduino.h>
#include "sensor_wrapper.h"

void initDB();
int writeReadings(READINGS *readings);

#endif