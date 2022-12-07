#ifndef SENSOR_WRAPPER_H
#define SENSOR_WRAPPER_H

#include <Arduino.h>

#define BTN_PIN 23
#define RELAY_PIN 17
#define MAX_STRING_LENGTH 9
#define JSON_SIZE 192

typedef struct Readings{
    float voltage;
    float current;
    float power;
    float capacityAh;
    float capacityWh;
    char strVoltage[MAX_STRING_LENGTH];
    char strCurrent[MAX_STRING_LENGTH];
    char strPower[MAX_STRING_LENGTH];
    char strCapacityAh[MAX_STRING_LENGTH];
    char strCapacityWh[MAX_STRING_LENGTH];
}READINGS;

typedef struct Limits{
    bool lowVoltageLimitEnabled = false;
    bool highVoltageLimitEnabled = false;
    bool overCurrentLimitEnabled = false;
    bool overPowerLimitEnabled = false;

    float lowVoltageLimit;
    float highVoltageLimit;
    float overCurrentLimit;
    float overPowerLimit;
}LIMITS;

bool setupINA();
float getVoltage();
float getCurrent();
void processReadings(READINGS *readings, unsigned long *lastTime);
void serializeReadings(READINGS *readings, char *output);
void updateLimits(char *message);
void resetLimits();
bool protectionTriggered(READINGS *readings);

#endif