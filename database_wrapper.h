#ifndef DATABASE_WRAPPER_H
#define DATABASE_WRAPPER_H

#include <Arduino.h>
#include "sensor_wrapper.h"

void initDB();
int writeReadingsToDb(READINGS *readings);
void getDbReadings(const char* timeFrom, const char* timeTo);

#endif